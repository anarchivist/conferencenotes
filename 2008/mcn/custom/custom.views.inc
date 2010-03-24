<?php

/**
 * Implementation of hook_views_data()
 */
function custom_views_data() {

  $data['amazon_import']['table']['group']  = t('Remote Amazon Data');
  $data['amazon_import']['table']['base'] = array(
    'field' => 'asin',
    'title' => t('Amazon product'),
    'help' => t('Imported Amazon product data'),
  );

  $data['amazon_import']['asin'] = array(
    'title' => t('ASIN'),
    'help' => t('Amazon\'s unique product ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_amazon_asin',
      'name field' => 'title',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['amazon_import']['title'] = array(
    'title' => t('Title'),
    'help' => t('Product title'),
    'field' => array(
      'handler' => 'views_handler_field_amazon_title',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'title',
      'numeric' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['amazon_import']['isbn'] = array(
    'title' => t('ISBN'),
    'help' => t('ISBN number'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'title',
      'numeric' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['amazon_import']['publication_date'] = array(
    'title' => t('Publication date'),
    'help' => t('Publication date of this book product'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'name field' => 'title',
      'numeric' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['amazon_import']['price'] = array(
    'title' => t('Price'),
    'help' => t('List price in US Dollars'),
    'field' => array(
      'handler' => 'views_handler_field_amazon_price',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_amazon_price',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
  );
  $data['amazon_import']['publisher'] = array(
    'title' => t('Publisher'),
    'help' => t('The publisher of the book'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'title',
      'numeric' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_amazon_publisher',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['amazon_import']['detail_url'] = array(
    'title' => t('Detail URL'),
    'help' => t('The URL on Amazon\'s site for this product'),
    'field' => array(
      'handler' => 'views_handler_field_amazon_url',
      'click sortable' => FALSE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => 'title',
      'numeric' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );


  $sizes = array(
    'smallimage' => 'Small image',
    'mediumimage' => 'Medium image',
    'largeimage' => 'Large image',
  );

  foreach ($sizes as $size => $label) {
    $table_alias = 'amazon_import_images_'. $size;
    $data[$table_alias]['table']['group'] = t('Remote Amazon Data');
    $data[$table_alias]['table']['join']['amazon_import'] = array(
      'table' => 'amazon_import_images',
      'left_table' => 'amazon_import',
      'left_field' => 'asin',
      'field' => 'asin',
      'extra' => array(
        array(
          'field' => 'size',
          'operator' => '=',
          'value' => $size,
        ),
      ),
    );
    $data[$table_alias]['url'] = array(
      'title' => t($label),
      'help' => t($label .' of this product'),
      'field' => array(
        'handler' => 'views_handler_field_amazon_image',
      ),
    );
  }




  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function custom_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'custom') . '/views',
    ),
    'handlers' => array(
      'views_handler_field_amazon_url' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_amazon_title' => array(
        'parent' => 'views_handler_field_url',
      ),
      'views_handler_field_amazon_price' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_amazon_image' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_filter_amazon_price' => array(
        'parent' => 'views_handler_filter_numeric',
      ),
      'views_handler_filter_amazon_publisher' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'views_handler_argument_amazon_asin' => array(
        'parent' => 'views_handler_argument_string',
      ),
    ),
  );
}
