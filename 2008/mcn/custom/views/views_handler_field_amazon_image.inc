<?php

class views_handler_field_amazon_image extends views_handler_field {
  /**
   * Constructor to provide additional field to add.
   */
  function construct() {
    parent::construct();
    $this->additional_fields = array(
      'height' => 'height',
      'width' => 'width',
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    return theme('image', $value, '', '', array('height' => $values->height, 'width' => $values->width), FALSE);
  }
}
