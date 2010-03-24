<?php

class views_handler_argument_amazon_asin extends views_handler_argument_string {

  /**
   * Override the behavior of title(). Get the title of the product.
   */
  function title() {
    $titles = array();
    $placeholders = db_placeholders($this->argument, 'varchar');

    $result = db_query("SELECT title FROM {amazon_import} WHERE asin IN ($placeholders)", $this->argument);
    while ($term = db_fetch_object($result)) {
      $titles[] = check_plain($term->title);
    }
    return implode(', ',  $titles);
  }
}
