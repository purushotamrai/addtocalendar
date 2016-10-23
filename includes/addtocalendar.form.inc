<?php

/**
 * @file
 * Contains form for addtocalendar module.
 */

/**
 * Creates Settings form.
 * @param $settings
 * Third party Settings array.
 * @param $field_definition
 * Field Definition of current field.
 * @return array
 */
function _addtocalendar_build_form($settings, $field_definition) {
  $element = [];

  $element['addtocalendar_show'] = [
    '#type' => 'checkbox',
    '#title' => t('Show Add to Calendar'),
    '#default_value' => $settings['addtocalendar_show'],
  ];

  $element['addtocalendar_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Add to Calendar Settings'),
    '#states' => [
      'visible' => [
        'input[name*="addtocalendar_show"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $element['addtocalendar_settings']['style'] = [
    '#type' => 'select',
    '#title' => t('Select Style'),
    '#options' => [
      0 => t('No Styling'),
      'blue' => t('Blue'),
      'glow_orange' => t('Glow Orange'),
    ],
    '#default_value' => !empty($settings['addtocalendar_settings']['style']) ? $settings['addtocalendar_settings']['style'] : 'blue',
  ];

  $element['addtocalendar_settings']['display_text'] = [
    '#type' => 'textfield',
    '#title' => t('Display Text'),
    '#default_value' => !empty($settings['addtocalendar_settings']['display_text']) ? $settings['addtocalendar_settings']['display_text'] : t('Add to Calender'),
  ];

  $info = [
    'atc_title' => t('Title'),
    'atc_description' => t('Description'),
    'atc_location' => t('Location'),
    'atc_organizer' => t('Organizer'),
    'atc_organizer_email' => t('Organizer email'),
    'atc_date_end' => t('End Date'),
  ];

  $fields = Drupal::service('entity_field.manager')->getFieldDefinitions($field_definition->get('entity_type'), $field_definition->get('bundle'));
  $field_options = [];

  foreach ($fields as $id => $field) {
    if (is_a($field, 'Drupal\field\Entity\FieldConfig')) {
      $field_options[$id] = $field->getLabel();
    }
  }

  $field_options = array_merge(
    ['token' => t('Use Token/Static Content')],
    ['title' => t('Title')],
    $field_options
  );

  if (\Drupal::moduleHandler()->moduleExists('token')) {
    $element['addtocalendar_settings']['token_help'] = [
      '#type' => 'markup',
      '#token_types' => array('node'),
      '#theme' => 'token_tree_link',
    ];
  }

  foreach ($info as $id => $label) {
    $element['addtocalendar_settings'][$id]['field'] = [
      '#type' => 'select',
      '#title' => $label . t(': field'),
      '#options' => $field_options,
      '#description' => t('Select field to be used as @label for calendar events', array('@label' => $label)),
      '#default_value' => !empty($settings['addtocalendar_settings'][$id]['field']) ? $settings['addtocalendar_settings'][$id]['field'] : '',
    ];
    $element['addtocalendar_settings'][$id]['tokenized'] = [
      '#type' => 'textfield',
      '#title' => $label . t(': Static/Tokenized Content'),
      '#default_value' => !empty($settings['addtocalendar_settings'][$id]['tokenized']) ? $settings['addtocalendar_settings'][$id]['tokenized'] : '',
    ];
  }

  $element['addtocalendar_settings']['atc_privacy'] = [
    '#type' => 'select',
    '#title' => t('Privacy'),
    '#options' => [
      'public' => t('Public'),
      'private' => t('Private'),
    ],
    '#description' => t('Use public for free access to event information from any places. User private if the event is closed to public access.'),
    '#default_value' => !empty($settings['addtocalendar_settings']['atc_privacy']) ? $settings['addtocalendar_settings']['atc_privacy'] : '',
  ];
  $element['addtocalendar_settings']['data_secure'] = [
    '#type' => 'select',
    '#title' => t('Security level'),
    '#options' => [
      'auto' => t('Auto'),
      'true' => t('Use https only'),
      'false' => t('Use http only'),
    ],
    '#default_value' => !empty($settings['addtocalendar_settings']['data_secure']) ? $settings['addtocalendar_settings']['data_secure'] : '',
  ];
  $element['addtocalendar_settings']['data_calendars'] = [
    '#type' => 'checkboxes',
    '#options' => [
      'iCalendar' => t('iCalendar'),
      'Google Calendar' => t('Google Calendar'),
      'Outlook' => t('Outlook'),
      'Outlook Online' => t('Outlook Online'),
      'Yahoo! Calendar' => t('Yahoo! Calendar'),
    ],
    '#default_value' => !empty($settings['addtocalendar_settings']['data_calendars']) ? $settings['addtocalendar_settings']['data_calendars'] : '',
    '#title' => t('List of calendars to show in button list.'),
  ];

  return $element;
}
