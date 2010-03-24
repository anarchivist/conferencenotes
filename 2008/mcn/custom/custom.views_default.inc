<?php

/**
 * @file
 *
 * Default views specific to this site.
 *
 * @copyright (C) Copyright 2009 Palantir.net
 * @license http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Implementation of hook_views_default_views().
 */
function custom_views_default_views() {
  $view = new view;
  $view->name = 'amazon_products';
  $view->description = 'Demo for Museums on the Web';
  $view->tag = 'matw';
  $view->view_php = '';
  $view->base_table = 'amazon_import';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'display_as_link' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'amazon_import',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'isbn' => array(
      'label' => 'ISBN',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'isbn',
      'table' => 'amazon_import',
      'field' => 'isbn',
      'relationship' => 'none',
    ),
    'price' => array(
      'label' => 'Price',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'id' => 'price',
      'table' => 'amazon_import',
      'field' => 'price',
      'relationship' => 'none',
    ),
    'publication_date' => array(
      'label' => 'Publication date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'custom',
      'custom_date_format' => 'j F Y',
      'exclude' => 0,
      'id' => 'publication_date',
      'table' => 'amazon_import',
      'field' => 'publication_date',
      'relationship' => 'none',
    ),
    'publisher' => array(
      'label' => 'Publisher',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'publisher',
      'table' => 'amazon_import',
      'field' => 'publisher',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'amazon_import',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'publisher' => array(
      'operator' => 'in',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'publisher_op',
        'identifier' => 'publisher',
        'label' => 'Publisher',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'case' => 1,
      'id' => 'publisher',
      'table' => 'amazon_import',
      'field' => 'publisher',
      'relationship' => 'none',
    ),
    'price' => array(
      'operator' => '<=',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 1,
        'operator' => 'price_operator',
        'identifier' => 'price',
        'label' => 'Price',
        'optional' => 1,
        'remember' => 0,
      ),
      'id' => 'price',
      'table' => 'amazon_import',
      'field' => 'price',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('empty', 'Sorry, no products match those criteria.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'isbn' => 'isbn',
      'price' => 'price',
      'publication_date' => 'publication_date',
      'publisher' => 'publisher',
      'detail_url' => 'detail_url',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'isbn' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'price' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'publication_date' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'publisher' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'detail_url' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'view/amazon');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'amazon_product';
  $view->description = 'A single amazon product';
  $view->tag = 'matw';
  $view->view_php = '';
  $view->base_table = 'amazon_import';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'detail_url' => array(
      'label' => 'Amazon link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'detail_url',
      'table' => 'amazon_import',
      'field' => 'detail_url',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'isbn' => array(
      'label' => 'ISBN',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'isbn',
      'table' => 'amazon_import',
      'field' => 'isbn',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'price' => array(
      'label' => 'Price',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'price',
      'table' => 'amazon_import',
      'field' => 'price',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'publication_date' => array(
      'label' => 'Publication date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'custom',
      'custom_date_format' => 'j F Y',
      'exclude' => 0,
      'id' => 'publication_date',
      'table' => 'amazon_import',
      'field' => 'publication_date',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'publisher' => array(
      'label' => 'Publisher',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'publisher',
      'table' => 'amazon_import',
      'field' => 'publisher',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'url' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'url',
      'table' => 'amazon_import_images_mediumimage',
      'field' => 'url',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'asin' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(
        'count' => 1,
        'override' => 0,
        'items_per_page' => '25',
      ),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'id' => 'asin',
      'table' => 'amazon_import',
      'field' => 'asin',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'amazon_product' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'user_argument_type' => '',
      'restrict_user_roles' => 0,
      'user_roles' => array(),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 1);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'view/product/%');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

  return $views;
}
