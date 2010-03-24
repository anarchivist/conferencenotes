<?php

/**
 * Load a product.
 *
 * @param string $asin
 * @return Product
 */
function product_load($asin) {
  static $products;

  if (!isset($products[$asin])) {
    $products[$asin] = new Product($asin);
  }

  return $products[$asin];
}

function product_load_multiple($asins) {
  return new ProductSet($asins);
}

class Product {

  protected $asin;

  protected $data;

  function __construct($asin) {
    if (is_array($asin)) {
      $this->asin = $asin['asin'];
      $this->data = $asin;
    }
    else {
      $this->asin = $asin;

      // amazon_item_lookup() does type checking for strings and arrays, but
      // in some circumstances the ASIN could be an int.
      $items = amazon_item_lookup((string)$this->asin);
      $this->data = current($items);
    }
  }

  public function id() {
    return $this->asin;
  }

  public function title() {
    return $this->data['title'];
  }

  public function getRawInfo() {
    return $this->data;
  }

  public function getField($field) {
    return isset($this->data[$field]) ? $this->data[$field] : '';
  }

}

class ProductSet implements IteratorAggregate {

  protected $products;

  function __construct(array $asins) {
    $items = amazon_item_lookup($asins);
    foreach ($items as $item) {
      $this->products[$item['asin']] = new Product($item);
    }
  }

  public function getIterator() {
    return new ArrayIterator($this->products);
  }

  public function title() {
    $titles = array();
    foreach ($this->products as $product) {
      $titles[] = $product->title();
    }
    return implode(', ', $titles);
  }

  public function getRawInfo() {
    $info = array();
    foreach ($this->products as $product) {
      $info[$product->id()] = $product->getRawInfo();
    }
    return $info;
  }

  public function getField($field) {
    $info = array();
    foreach ($this->products as $product) {
      $info[$product->id()] = $product->getField($field);
    }
    return $info;
  }

}
