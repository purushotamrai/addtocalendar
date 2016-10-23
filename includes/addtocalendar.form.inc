<?php

/**
 * @file
 */

/**
 * Implements hook_forms().
 */

/**
 *
 */
function _addtocalendar_build_form($settings, $field) {
  $bundle_name = $field['bundles'][$instance['entity_type']][0];
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $field_list = field_info_instances($instance['entity_type'], $bundle_name);
  $element['addtocalendar_show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Add to Calendar'),
    '#default_value' => $settings['addtocalendar_show'],
  );

  $element['addtocalendar_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add to Calendar Settings'),
    '#states' => array(
      "visible" => array(
        "input[name*='addtocalendar_show']" => array("checked" => TRUE),
      ),
    ),
  );

  $element['addtocalendar_settings']['style'] = array(
    '#type' => 'select',
    '#title' => t('Select Style'),
    '#options' => array(
      0 => t('No Styling'),
      'blue' => t('Blue'),
      'glow_orange' => t('Glow Orange'),
    ),
    '#default_value' => !empty($settings['addtocalendar_settings']['style']) ? $settings['addtocalendar_settings']['style'] : 'blue',
  );
  $element['addtocalendar_settings']['display_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Text'),
    '#default_value' => !empty($settings['addtocalendar_settings']['display_text']) ? $settings['addtocalendar_settings']['display_text'] : t('Add to Calender'),
  );
  $info = array(
    'atc_title' => t('Title'),
    'atc_description' => t('Description'),
    'atc_location' => t('Location'),
    'atc_organizer' => t('Organizer'),
    'atc_organizer_email' => t('Organizer email'),
    'atc_date_end' => t('End Date'),
  );
  $field_options = [];
  foreach ($field_list as $id => $field_i) {
    $field_options[$id] = $field_i['label'];
  }

  $field_options = array_merge(
    ['token' => t('Use Token/Static Content')],
    ['title' => t('Title')],
    $field_options
  );
  $info = array(
    'atc_title' => t('Title'),
    'atc_description' => t('Description'),
    'atc_location' => t('Location'),
    'atc_organizer' => t('Organizer'),
    'atc_organizer_email' => t('Organizer email'),
    'atc_date_end' => t('End Date'),
  );
  foreach ($info as $id => $label) {
    $element['addtocalendar_settings'][$id]['field'] = array(
      '#type' => 'select',
      '#title' => $label . t(': field'),
      '#options' => $field_options,
      '#description' => t('Select field to be used as @label for calendar events', array('@label' => $label)),
      '#default_value' => !empty($settings['addtocalendar_settings'][$id]['field']) ? $settings['addtocalendar_settings'][$id]['field'] : '',
    );
    $element['addtocalendar_settings'][$id]['tokenized'] = array(
      '#type' => 'textfield',
      '#title' => $label . t(': Static/Tokenized Content'),
      '#default_value' => !empty($settings['addtocalendar_settings'][$id]['tokenized']) ? $settings['addtocalendar_settings'][$id]['tokenized'] : '',
    );
  }

  $element['addtocalendar_settings']['atc_privacy'] = array(
    '#type' => 'select',
    '#title' => t('Privacy'),
    '#options' => array(
      'public' => t('Public'),
      'private' => t('Private'),
    ),
    '#description' => t('Use public for free access to event information from any places. User private if the event is closed to public access.'),
    '#default_value' => !empty($settings['addtocalendar_settings']['atc_privacy']) ? $settings['addtocalendar_settings']['atc_privacy'] : '',
  );
  $element['addtocalendar_settings']['data_secure'] = array(
    '#type' => 'select',
    '#title' => t('Security level'),
    '#options' => array(
      'auto' => t('Auto'),
      'true' => t('Use https only'),
      'false' => t('Use http only'),
    ),
    '#default_value' => !empty($settings['addtocalendar_settings']['data_secure']) ? $settings['addtocalendar_settings']['data_secure'] : '',
  );
  $element['addtocalendar_settings']['data_calendars'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'iCalendar' => t('iCalendar'),
      'Google Calendar' => t('Google Calendar'),
      'Outlook' => t('Outlook'),
      'Outlook Online' => t('Outlook Online'),
      'Yahoo! Calendar' => t('Yahoo! Calendar'),
    ),
    '#default_value' => !empty($settings['addtocalendar_settings']['data_calendars']) ? $settings['addtocalendar_settings']['data_calendars'] : '',
    '#title' => t('List of calendars to show in button list.'),
  );

  return $element;

}
