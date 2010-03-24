<?php

class views_handler_field_amazon_title extends views_handler_field_url {
  /**
   * Constructor to provide additional field to add.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['asin'] = 'asin';
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    if (!empty($this->options['display_as_link'])) {
      return l($value, 'view/product/'. $values->asin);
    }
    else {
      return $value;
    }
  }
}
