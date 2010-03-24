<?php

/**
 * Form builder for import admin.
 */
function custom_product_admin_import(&$form_state) {
  $form = array();

  $form['import'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

function custom_product_admin_import_submit($form, &$form_state) {
  $items = amazon_search_simple_search('drupal');

  db_query("DELETE FROM {amazon_import}");
  db_query("DELETE FROM {amazon_import_images}");

  foreach (array_keys($items) as $asin) {
    $product = product_load($asin);

    db_query("INSERT INTO {amazon_import} (asin, title, isbn, publication_date, price, publisher, detail_url) VALUES ('%s', '%s', '%s', %d, %d, '%s', '%s')", array(
      $product->getField('asin'),
      $product->getField('title'),
      $product->getField('isbn'),
      strtotime($product->getField('publicationdate')),
      $product->getField('listpriceamount'),
      $product->getField('publisher'),
      $product->getField('detailpageurl'),
    ));

    foreach ($product->getField('imagesets') as $size => $imageset) {
      db_query("INSERT INTO {amazon_import_images} (asin, size, url, height, width) VALUES ('%s', '%s', '%s', %d, %d)", array(
        $product->getField('asin'),
        $size,
        $imageset['url'],
        $imageset['height'],
        $imageset['width'],
      ));
    }

    // So that the page cache doesn't get stale.
    cache_clear_all();
  }


  drupal_set_message(t('Dataset has been rebuilt.'));
}

