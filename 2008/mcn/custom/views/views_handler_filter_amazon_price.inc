<?php

class views_handler_filter_amazon_price extends views_handler_filter_numeric {
  /**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
    $this->ensure_my_table();
    $value = $this->value['value'] * 100; // This field is stored as an integer, because that's what Amazon gives us.
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field " . $this->operator . " '%s'", $value);
  }
}
