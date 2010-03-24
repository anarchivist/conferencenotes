<?php

class views_handler_filter_amazon_publisher extends views_handler_filter_in_operator {

  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Publisher');
      $result = db_query("SELECT DISTINCT publisher FROM {amazon_import} ORDER BY publisher");
      while ($record = db_fetch_object($result)) {
        $options[$record->publisher] = $record->publisher;
      }
      $this->value_options = $options;
    }
  }
}
