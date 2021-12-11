<?php
/**
 * @file
 * Theme functions for the Glightbox module.
 */

/**
 * Returns HTML for a Glightbox lightbox.
 *
 * @param array $variables
 *   An associative array containing:
 *   - item: An array of image data.
 *   - content_image_style: The image style to use for the content image.
 *   - lightbox_image_style: The image style to use for the lightbox image.
 *   - title_src: Field name or image attribute to use for the lightbox title.
 *   - description_src: Field name or image attribute to use for the lightbox description.
 *   - data_src: Node or view data needed to retrieve text for lightbox caption(title and description).
 *   - desc_position: Field name or image attribute that contains info about caption position within lightbox.
 *   - gallery_id: data attribute value that defines what gallery the image belongs to.
 *
 * @ingroup themeable
 */
function theme_glightbox($variables = array()) {
  backdrop_add_library('glightbox', 'glightbox', FALSE);
  backdrop_add_js(array('glightbox' => config_get('glightbox.settings')), 'setting');
  backdrop_add_js(backdrop_get_path('module', 'glightbox') . '/js/glightbox.js');

  $item = $variables['item'];

  // Generate content image.
  $image_variables = array(
    'uri'    => $item['uri'],
    'width'  => $item['width'],
    'height' => $item['height'],
    'alt'    => $item['alt'],
    'title'  => $item['title'],
  );
  if (!empty($variables['content_image_style'])) {
    $image_variables['style_name'] = $variables['content_image_style'];
    $image = theme('image_style', $image_variables);
  }
  else {
    $image = theme('image', $image_variables);
  }

  // Generate lightbox image URL.
  if (!empty($variables['lightbox_image_style'])) {
    $url = image_style_url($variables['lightbox_image_style'], $item['uri']);
  }
  else {
    $url = file_create_url($item['uri']);
  }

  // Extract caption text from views or node data or get it from image tags.
  $title_text       = get_text_from_data($variables['title_src'],       $item, $variables['data_src']);
  $description_text = get_text_from_data($variables['description_src'], $item, $variables['data_src']);
  $desc_position    = get_text_from_data($variables['desc_position'],   $item, $variables['data_src']);

  // Generate link options.
  $options = array(
    'html' => TRUE,
    'attributes' => array(
      'class'            => array('glightbox'),
      'data-gallery'     => $variables['gallery_id'],
    ),
  );

  // Add title attribute if title text is provided.
  if (!empty($title_text)) {
    $options['attributes']['data-title'] = $title_text;
  }

  // Add description attribute if description text is provided.
  if (!empty($description_text)) {
    $options['attributes']['data-description'] = $description_text;
  }

  // Add description position attribute if specified.
  if (!empty($desc_position)) {
    $desc_position = strtolower(strip_tags($desc_position));
    $valid_values = array('bottom', 'top', 'left', 'right');
    if (in_array($desc_position, $valid_values)) {
      $options['attributes']['data-desc-position'] = $desc_position;
    }
  }

  return l($image, $url, $options);
}

/**
 * Returns text for lightbox caption from views or node fields or image tags.
 */
function get_text_from_data($text_src, $item, $data_src) {
  $result = '';
  switch ($text_src) {
    case 'alt_tag':
      $result = $item['alt'];
      break;
    case 'title_tag':
      $result = $item['title'];
      break;
    case 'node_title':
      if (isset($data_src['node'])) {
        $result = $data_src['node']->title;
      }
      break;
    default:
      if (isset($data_src['view'])) {
        // Get text data from views field.
        $result = $data_src['view']->style_plugin->get_field($data_src['row'], $text_src);
      }
      elseif (isset($data_src['node'])) {
        // Get text data from node field.
        $items = field_get_items('node', $data_src['node'], $text_src, $data_src['langcode']);
        $field = field_view_value('node', $data_src['node'], $text_src, $items[0], $data_src['view_mode'], $data_src['langcode']);
        $result = backdrop_render($field);
      }
  }
  return $result;
}