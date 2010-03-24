<?php

class views_handler_field_amazon_url extends views_handler_field {

  function render($values) {
    $value = $values->{$this->field_alias};
    return l(t('Amazon page'), $value);
  }
}
