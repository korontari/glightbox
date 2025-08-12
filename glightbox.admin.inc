<?php
/**
 * @file
 * Administration inteface for GLightbox.
 */
function glightbox_admin_form($form, &$form_state) {
  $config = config('glightbox.settings');

  // Themes setting reserved for future implementation.
  $form['theme'] = array(
    '#type' => 'hidden',
    '#value' => 'default',
    '#default_value' => $config->get('theme'),
  );

  $form['preload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Preload images'),
    '#default_value' => $config->get('preload'),
  );

  // Effects.
  $form['effects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Effects'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['effects']['open'] = array(
    '#type' => 'select',
    '#title' => t('Open effect'),
    '#options' => array(
        'zoom' => t('Zoom'),
        'fade' => t('Fade'),
        'none' => t('None'),
      ),
    '#default_value' => $config->get('effect_open'),
    '#description' => t('Lightbox opening effect.'),
  );

  $form['effects']['close'] = array(
    '#type' => 'select',
    '#title' => t('Close effect'),
    '#options' => array(
        'zoom' => t('Zoom'),
        'fade' => t('Fade'),
        'none' => t('None'),
      ),
    '#default_value' => $config->get('effect_close'),
    '#description' => t('Lightbox closing effect.'),
  );

  $form['effects']['slide'] = array(
    '#type' => 'select',
    '#title' => t('Slide effect'),
    '#options' => array(
        'slide' => t('Slide'),
        'zoom'  => t('Zoom'),
        'fade'  => t('Fade'),
        'none'  => t('None'),
      ),
    '#default_value' => $config->get('effect_slide'),
    '#description' => t('Effect on slide change.'),
  );

  // Interface.
  $form['ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interface'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ui']['close_btn'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display close button'),
    '#default_value' => $config->get('ui_close_btn'),
  );

  $form['ui']['close_outside'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close on outside click'),
    '#default_value' => $config->get('ui_close_outside'),
    '#description' => t('Close the lightbox when clicking outside the active slide.'),
  );

  $form['ui']['caption_pos'] = array(
    '#type' => 'select',
    '#title' => t('Caption position'),
    '#options' => get_caption_position_options(),
    '#default_value' => $config->get('ui_caption_pos'),
    '#description' => t('Position of the caption (which includes the <em>Title</em> and <em>Description</em> fields) in the lightbox. When <em>Automatic</em> mode is enabled, captions are placed vertically or horizontally based on the image’s width-to-height ratio (aspect ratio). See <em>Advanced settings</em> below to fine-tune this mode.'),
  );

  $form['ui']['more_text'] = array(
    '#type' => 'textfield',
    '#title' => t('More text'),
    '#default_value' => $config->get('ui_more_text'),
    '#size' => 32,
    '#maxlength' => 32,
    '#description' => t('<em>More</em> text for descriptions on mobile devices.'),
  );

  $form['ui']['more_length'] = array(
    '#type' => 'number',
    '#title' => t('More length'),
    '#default_value' => $config->get('ui_more_length'),
    '#min' => 0,
    '#max' => 999,
    '#size' => 3,
    '#description' => t('Number of characters to display on the description before adding the <em>more text</em> link (only for mobiles). Setting it to zero will display the entire description.'),
  );

  // Settings for automatic caption positioning.
  $form['ui']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ui']['advanced']['auto_aspect_ratio'] = array(
    '#type' => 'number',
    '#title' => t('Caption orientation breakpoint'),
    '#default_value' => $config->get('ui_auto_aspect_ratio'),
    '#min' => 0.1,
    '#max' => 3.0,
    '#step' => 0.1,
    '#size' => 2,
    '#description' => t('The value you set here is the width-to-height ratio used to decide caption orientation when in <em>Automatic</em> mode. For example, if set to 1.0 (a square), images with a ratio below 1.0 (portrait) will have a vertical caption, while images with a ratio above 1.0 (landscape) will have a horizontal caption. Default breakpoint is 1.3 (approximate ratio of a 4:3 landscape image).'),
  );

  $form['ui']['advanced']['auto_horiz_pos'] = array(
    '#type' => 'select',
    '#title' => t('Auto horizontal position'),
    '#options' => array(
      'bottom' => t('Bottom'),
      'top'    => t('Top'),
    ),
    '#default_value' => $config->get('ui_auto_horiz_pos'),
    '#description' => t('Preferred horizontal caption position in <em>Automatic</em> mode.'),
  );

  $form['ui']['advanced']['auto_vert_pos'] = array(
    '#type' => 'select',
    '#title' => t('Auto vertical position'),
    '#options' => array(
      'right'  => t('Right'),
      'left'   => t('Left'),
    ),
    '#default_value' => $config->get('ui_auto_vert_pos'),
    '#description' => t('Preferred vertical caption position in <em>Automatic</em> mode.'),
  );

  // Navigation
  $form['navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['navigation']['loop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop slides'),
    '#default_value' => $config->get('navigation_loop'),
    '#description' => t('Loop slides on end.'),
  );

  $form['navigation']['touch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Touch navigation'),
    '#default_value' => $config->get('navigation_touch'),
    '#description' => t('Enable the touch navigation(swipe).'),
  );

  $form['navigation']['touch_follow_axis'] = array(
    '#type' => 'checkbox',
    '#title' => t('Touch follow axis'),
    '#default_value' => $config->get('navigation_touch_follow_axis'),
    '#description' => t('Image will follow axis when dragging on mobile device.'),
    '#states' => array(
      'visible' => array(
        ':input[name="touch"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['navigation']['keyboard'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keyboard navigation'),
    '#default_value' => $config->get('navigation_keyboard'),
    '#description' => t('Enable the keyboard navigation.'),
  );

  $form['navigation']['zoomable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Zoom'),
    '#default_value' => $config->get('navigation_zoomable'),
    '#description' => t('Enable zoomable images.'),
  );

  $form['navigation']['draggable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mouse drag'),
    '#default_value' => $config->get('navigation_draggable'),
    '#description' => t('Enable mouse drag to go to previous and next slide (only images and inline content).'),
  );

  $form['navigation']['drag_tolerance_x'] = array(
    '#type' => 'number',
    '#title' => t('Drag tolerance X'),
    '#default_value' => $config->get('navigation_drag_tolerance_x'),
    '#min' => 0,
    '#max' => 999,
    '#size' => 3,
    '#field_suffix' => t('pix'),
    '#description' => t('Number of pixels the user has to drag to go to previous or next slide.'),
    '#states' => array(
      'visible' => array(
        ':input[name="draggable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['navigation']['drag_tolerance_y'] = array(
    '#type' => 'number',
    '#title' => t('Drag tolerance Y'),
    '#default_value' => $config->get('navigation_drag_tolerance_y'),
    '#min' => 0,
    '#max' => 999,
    '#size' => 3,
    '#field_suffix' => t('pix'),
    '#description' => t('Number of pixels the user has to drag up or down to close the lightbox. Zero value disables vertical drag.'),
    '#states' => array(
      'visible' => array(
        ':input[name="draggable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['navigation']['drag_auto_snap'] = array(
    '#type' => 'checkbox',
    '#title' => t('Drag auto snap'),
    '#default_value' => $config->get('navigation_drag_auto_snap'),
    '#description' => t('If enabled the slide will automatically change to prev/next or close if <em>Drag tolerance X</em> or <em>Drag tolerance Y</em> is reached, otherwise it will wait till the mouse is released.'),
    '#states' => array(
      'visible' => array(
        ':input[name="draggable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['#validate'][] = 'glightbox_form_validate';

  // Submit button.
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validation function, ensures that text input is safe.
 */
function glightbox_form_validate($form, &$form_state) {
  $form_state['values']['more_text'] = check_plain($form_state['values']['more_text']);
}

/**
 * Saves configuration settings when the form is submitted.
 */
function glightbox_admin_form_submit($form, &$form_state) {
  $config = config('glightbox.settings');

  $config->set('preload', $form_state['values']['preload']);
  $config->set('effect_open', $form_state['values']['open']);
  $config->set('effect_close', $form_state['values']['close']);
  $config->set('effect_slide', $form_state['values']['slide']);
  $config->set('ui_close_btn', $form_state['values']['close_btn']);
  $config->set('ui_close_outside', $form_state['values']['close_outside']);
  $config->set('ui_caption_pos', $form_state['values']['caption_pos']);
  $config->set('ui_more_text', $form_state['values']['more_text']);
  $config->set('ui_more_length', $form_state['values']['more_length']);
  $config->set('ui_auto_aspect_ratio', $form_state['values']['auto_aspect_ratio']);
  $config->set('ui_auto_horiz_pos', $form_state['values']['auto_horiz_pos']);
  $config->set('ui_auto_vert_pos', $form_state['values']['auto_vert_pos']);
  $config->set('navigation_loop', $form_state['values']['loop']);
  $config->set('navigation_touch', $form_state['values']['touch']);
  $config->set('navigation_touch_follow_axis', $form_state['values']['touch_follow_axis']);
  $config->set('navigation_keyboard', $form_state['values']['keyboard']);
  $config->set('navigation_zoomable', $form_state['values']['zoomable']);
  $config->set('navigation_draggable', $form_state['values']['draggable']);
  $config->set('navigation_drag_tolerance_x', $form_state['values']['drag_tolerance_x']);
  $config->set('navigation_drag_tolerance_y', $form_state['values']['drag_tolerance_y']);
  $config->set('navigation_drag_auto_snap', $form_state['values']['drag_auto_snap']);

  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
