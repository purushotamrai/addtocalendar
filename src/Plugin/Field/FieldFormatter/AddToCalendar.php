<?php

namespace Drupal\addtocalendar\Plugin\Field\FieldFormatter;

use Drupal\Component\Utility\Html;
use Drupal\Core\Field\FieldItemInterface;
use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Field\FormatterBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\datetime\Plugin\Field\FieldFormatter\DateTimeDefaultFormatter;
use Drupal\datetime_range\DateTimeRangeTrait;

/**
 * Plugin implementation of the 'add_to_calendar' formatter.
 *
 * @FieldFormatter(
 *   id = "add_to_calendar",
 *   label = @Translation("Add to calendar"),
 *   field_types = {
 *     "datetime"
 *   }
 * )
 */
class AddToCalendar extends DateTimeDefaultFormatter {

  /**
   * {@inheritdoc}
   */
  public static function defaultSettings() {
    $addtocalendar_settings = ['style' => 'glow_orange'];
    return [
      'addtocalendar_show' => '1',
      'addtocalendar_settings'=> $addtocalendar_settings,
    ] + parent::defaultSettings();
  }

  /**
   * {@inheritdoc}
   */
  public function settingsForm(array $form, FormStateInterface $form_state) {
    $form = parent::settingsForm($form, $form_state);
    // dsm(get_class_methods($this));
    // dsm($this->getThirdPartySettings());
    $field_definition = $this->fieldDefinition;
    $settings = $this->getSettings();
    // dsm($settings);
    $form += _addtocalendar_build_form($settings, $field_definition);
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function settingsSummary() {
    $summary = [];
    $summary = parent::settingsSummary();
    // Implement settings summary.

    return $summary;
  }

    /**
   * {@inheritdoc}
   */
  public function viewElements(FieldItemListInterface $items, $langcode) {
    $elements = [];
    $settings = $this->getSettings();
    $multiple_value = $settings['addtocalendar_settings']['multiple_value'];
    foreach ($items as $delta => $item) {
      if ($item->date) {
        /** @var \Drupal\Core\Datetime\DrupalDateTime $date */
        dsm($delta);

        $show_calendar = false;
        $date = $item->date;
        $elements[$delta] = [
          'date' => $this->buildDateWithIsoAttribute($date),
        ];
        if($multiple_value == 2){
          $show_calendar = true;
        }
        else if($multiple_value == 1 && $delta == $settings['addtocalendar_settings']['delta']){
          $show_calendar = true;
        }
        if($show_calendar)
          $elements[$delta]['add_to_cal'] = ['#plain_text' => 'render add to calendar widget here'];

        if (!empty($item->_attributes)) {
          $elements[$delta]['#attributes'] += $item->_attributes;
          // Unset field item attributes since they have been included in the
          // formatter output and should not be rendered in the field template.
          unset($item->_attributes);
        }
      }
    }
    dsm($settings);
    return $elements;
  }

}
