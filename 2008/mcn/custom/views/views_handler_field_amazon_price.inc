<?php

class views_handler_field_amazon_price extends views_handler_field {

  function render($values) {
    $value = $values->{$this->field_alias};
    return theme('product_price', $value);
  }
}
