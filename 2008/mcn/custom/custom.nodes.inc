<?php

function custom_node_info() {
  return array(
    'amazon_product' => array(
      'name' => t('Amazon product'),
      'module' => 'amazon_product',
      'description' => t('Wrapper node for an amazon product.'),
    )
  );
}


function amazon_product_access($op, $node, $account = NULL) {

  global $user;
  $type = is_string($node) ? $node : (is_array($node) ? $node['type'] : $node->type);

  if ($op == 'create') {
    return user_access('create '. $type .' content');
  }

  if ($op == 'update' || $op == 'delete') {
    if (user_access('edit '. $type .' content') || (user_access('edit own '. $type .' content') && ($user->uid == $node->uid))) {
      return TRUE;
    }
  }
}

function amazon_product_form(&$node, $form_state) {
  $form = node_content_form($node, $form_state);

  return $form;
}


/**
 * Implementation of hook_load().
 */
function amazon_product_load($node) {

  // Get the asin ID for this product.
  $additions->amazon = db_fetch_array(db_query('SELECT asin FROM {amazon_asin} WHERE vid = %d', $node->vid));

  // Pull in the product object.
  if ($additions->amazon['asin']) {
    $additions->amazon['product'] = product_load($additions->amazon['asin']);

    // The only data we're caching into the local object is the product title.  This should
    // probably be done elsewhere, too, but meh.  Note that *this* load of the node is
    // unaffected, but later loads will be.  It's caching, so that's fine.
    if ($node->title != $additions->amazon['product']->title()) {
      db_query("UPDATE {node} SET title='%s', changed=%d WHERE vid=%d", $additions->amazon['product']->title(), time(), $node->vid);
      db_query("UPDATE {node_revisions} SET title='%s', timestamp=%d WHERE vid=%d", $additions->amazon['product']->title(), time(), $node->vid);
    }
  }
  return $additions;
}

/**
 * Implementation of hook_insert().
 */
function amazon_product_insert($node) {
  db_query("INSERT INTO {amazon_asin} (vid, nid, asin) VALUES (%d, %d, '%s')", $node->vid, $node->nid, $node->amazon['asin']);
}

/**
 * Implementation of hook_update().
 */
function amazon_product_update($node) {
  // if this is a new node or we're adding a new revision.
  if ($node->revision) {
    product_insert($node);
  }
  else {
    db_query("UPDATE {amazon_asin} SET asin = '%d' WHERE vid = %d", $node->amazon['asin'], $node->vid);
  }
}

/**
 * Implementation of hook_delete().
 */
function amazon_product_delete($node) {
  // Notice that we're matching all revision, by using the node's nid.
  db_query('DELETE FROM {amazon_asin} WHERE nid = %d', $node->nid);
}

/**
 * Implementation of hook_view().
 */
function amazon_product_view($node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);

  if (isset($node->amazon['product'])) {
    // This function gets called by pathauto (I think) or some such module when the node is first
    // being created, and the object is not loaded.  Therefore we have to have this check
    // in here.

    $node->content['asin'] = array(
      '#value' => $node->amazon['asin'],
      '#weight' => 1,
      '#hidden' => TRUE,
      '#theme' => 'custom_node_element',
    );

    $product = $node->amazon['product'];
    $i = 1;

    foreach (array('manufacturer', 'binding', 'numberofpages') as $field) {
      $node->content[$field] = array(
        '#type' => 'markup',
        '#title' => drupal_ucfirst($field),
        '#value' => filter_xss($product->getField($field)),
        '#weight' => $i++,
        '#theme' => 'custom_node_element',
      );
    }

    // Get the largest image.
    $data = $product->getRawInfo();
    $image = end($data['imagesets']);
    $node->content['image'] = array(
      '#title' => t('Image'),
      '#value' => theme('image', $image['url'], $product->title(), $product->title(), array('height' => $image['height'], 'width' => $image['width']), FALSE),
      '#weight' => $i++,
      '#theme' => 'custom_node_element',
    );
  }

  return $node;
}

function product_load_by_asin($asin) {

  if ($nid = product_get_nid_by_asin($asin)) {
    return node_load($nid);
  }

}

function product_get_nid_by_asin($asin) {
  return db_result(db_query_range("SELECT nid FROM {amazon_asin} WHERE asin = '%s'", $asin, 0, 1));
}

function custom_product_import_page($asin = NULL) {

  if (empty($asin)) {
    drupal_set_message('No ASIN specified to import into a node.');
    drupal_goto('');
  }

  $nid = product_get_nid_by_asin($asin);
  if (!$nid) {
    $node = custom_product_import_asin($asin);
    $nid = $node->nid;
  }

  drupal_goto('node/'. $nid);
}

/**
 * Menu callback; import a product as a node.
 *
 * @param $asin
 *   The asin of the product to import.
 * @return
 *  The just-created node object
 */
function custom_product_import_asin($asin) {
  $product = product_load($asin);

  $node = (object)array(
    'title' => $product->title(),
    'type' => 'amazon_product',
    // All product nodes are owned by uid 1 so that most users can't mess with them.
    'uid' => 1,
    'amazon' => array(
      'asin' => $asin,
    ),
  );

  node_save($node);

  return $node;
}


/**
 * Menu callback; search form.
 */
function custom_product_search_import_form($form_state) {
  $form['keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Keywords'),
    '#description' => t('Enter one or more keywords you want to search for.'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Look up products'),
  );

  if (isset($form_state['asins'])) {
    $products = new ProductSet($form_state['asins']);
    $rows = array();
    foreach ($products as $product) {
      $rows[] = array(
        l($product->title(), product_get_path($product)),
      );
    }
    $form['item_data'] = array(
      '#type' => 'markup',
      '#value' => theme('table', NULL, $rows),
      '#weight' => 10,
    );
  }
  return $form;
}

function custom_product_search_import_form_submit($form, &$form_state) {
  $products = array();
  $items = amazon_search_simple_search($form_state['values']['keywords']);

  $form_state['asins'] = array_keys($items);
  $form_state['rebuild'] = TRUE;
}

function product_get_path(Product $product) {
  $nid = product_get_nid_by_asin($product->id());
  if ($nid) {
    return 'node/'. $nid;
  }
  else {
    return 'product/import/'. $product->id();
  }
}
