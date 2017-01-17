<?php

/**
 * @file
 * Plugin to provide an relationship handler for profile entities.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Profile2 profile from user context'),
  'keyword' => 'profile2',
  'description' => t('Adds a profile2 entity as a relationship.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'context' => 'profile2_ctools_relationship_context',
  'edit form' => 'profile2_ctools_relationship_context_edit_form',
  'defaults' => array( 'profile_type' => '' ),
);

/**
 * Return a new context based on an existing context.
 */
function profile2_ctools_relationship_context($context, $conf) {
  $profile = null;

  if ( isset( $context->data, $context->data->uid, $conf['profile_type'] ) ) {
    $profile = profile2_load_by_user($context->data->uid, $conf['profile_type']);
  }

  if ( $profile ) {
    $relationship = ctools_context_create('entity:profile2', $profile);
  }
  else {
    $relationship = ctools_context_create_empty('entity:profile2');
  }

  return $relationship;
}

/**
 * Settings form for the relationship.
 */
function profile2_ctools_relationship_context_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach(profile2_get_types() as $key => $type){
    $options[ $key ] = $type->label;
  }

  $form['profile_type'] = array(
    '#type' => 'select',
    '#title' => t('Profile2 type'),
    '#description' => t('Select the profile2 type for this context.'),
    '#default_value' => $conf['profile_type'],
    '#prefix' => '<div class="clear-block no-float">',
    '#suffix' => '</div>',
    '#options' => $options
  );
  return $form;
}
