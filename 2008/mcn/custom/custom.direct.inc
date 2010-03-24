<?php

/**
 * Menu callback; individual project page.
 */
function custom_product_page(Product $product) {

  $output = theme('product', $product);

  //$output .= display($product, TRUE);

  return $output;
}

/**
 * Menu callback; search form.
 */
function custom_product_search_form($form_state) {
  $form['keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Keywords'),
    '#description' => t('Enter one or more keywords you want to search for.'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Look Up Products'),
  );

  if (isset($form_state['asins'])) {
    $products = new ProductSet($form_state['asins']);
    $rows = array();
    foreach ($products as $product) {
      $rows[] = array(
        l($product->title(), 'product/'. $product->id()),
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

function custom_product_search_form_submit($form, &$form_state) {
  $products = array();
  $items = amazon_search_simple_search($form_state['values']['keywords']);

  $form_state['asins'] = array_keys($items);
  $form_state['rebuild'] = TRUE;
}

/**
 * Theme function for a product object.
 *
 * @ingroup themeable
 * @param Product $product
 */
function theme_product($product) {
  return theme('amazon_item', $product->getRawInfo(), 'details');
}
