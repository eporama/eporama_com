<?php

/**
 * @file Drush sql commands
 */

/**
 * Implementation of hook_drush_help().
 */
function omega_tools_drush_help($section) {
  switch ($section) {
    case 'drush:omega-subtheme':
      return dt('Creates a valid Omega subtheme in sites/all/themes based on a single argument, the name of the subtheme');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function omega_tools_drush_command() {
  $items['omega-subtheme'] = array(
    'description' => 'Creates an Omega subtheme.',
    'callback' => 'drush_omega_subtheme',
    'examples' => array(
      'drush omega-subtheme "Subtheme Name"' => 'Create an HTML5 Omega subtheme to the default sites/all/themes folder named subtheme_name.',
      'drush omega-subtheme "Subtheme Name" html5' => 'Create an HTML5 Omega subtheme to the default sites/all/themes folder named subtheme_name.',
      'drush omega-subtheme "Subtheme Name" xhtml' => 'Create an XHTML Omega subtheme to the default sites/all/themes folder named subtheme_name.',
      'drush omega-subtheme "Subtheme Name" --destination=example.com' => 'Create an HTML5 Omega subtheme to sites/example.com/themes folder named subtheme_name.',
    ),
    'arguments' => array(
      'name' => 'The name of the subtheme to create.',
      'type' => 'The type of subtheme to create. XHTML or HTML5 (default)',
    ),
    'options' => array(
      '--destination' => 'The site specific folder name in /sites where the information should be saved. /sites/all by default.',
    ),
  );
  return $items;
}


function drush_omega_subtheme($name, $type = 'html5') {
  if (isset($name)) {
    $exec = drush_omega_tools_subtheme($name, $type);
    // Avoid the php memory of the $output array in drush_shell_exec().
    if ($exec) {
      $return = drush_op('system', $exec);
      return $return; 
    }
    
  }
  else {
    return drush_set_error(dt('You must delcare the name of the new subtheme. See drush help omega-subtheme for usage information.'));
  }
}

function drush_omega_tools_subtheme($name, $type) {
	$name_long = $name;
  // replace non-alphanumeric characters with an underscore
	$name = strtolower(preg_replace('/\W/', '_', $name));
	//clean up leading/trailing and double underscores
	$name = str_replace('__', '_', $name);
	$name = trim($name, '_');
	$drupal_root = drush_get_context('DRUSH_DRUPAL_ROOT') .'/';
	$type = strtolower($type);
	
  if ($path = drush_get_option('destination')) {
    $site_dir = $drupal_root .'sites/'. $path;
    $theme_dir = $site_dir .'/themes';
  }
  
  else {
  	$site_dir = $drupal_root .'sites/all';
  	$theme_dir = $site_dir .'/themes';
  }
  switch ($type) {
    case 'html5':
      $omega_path = $drupal_root . drupal_get_path('theme', 'starterkit_omega_html5');
    break;
    case 'xhtml':
      $omega_path = $drupal_root . drupal_get_path('theme', 'starterkit_omega_xhtml');
    break;
    default:
      drush_set_error(dt('The only valid arguments for $type are HTML5 (default) or XHTML. Please modify your command and try again. See drush help omega-subtheme for usage information.'));
      return FALSE;
    break;
  }
  if (!is_dir($omega_path)) {
    drush_set_error(dt('Omega base theme not found. You must download the Omega theme to create a subtheme of Omega. See drush help omega-subtheme for usage information.'));
  	return FALSE;
  }
  if (!is_dir($site_dir)) {
    drush_set_error(dt('The site directory: '. $site_dir .' does not exist. Please specify another, remove --destination to use /sites/all/themes. See drush help omega-subtheme for usage information.'));
    return FALSE;
  }
  if (!is_dir($theme_dir)) {
  	if(!drush_op('mkdir', $theme_dir)) {
      drush_set_error(dt('The theme directory: '. $theme_dir .' does not exist. An attempt to automagically create this folder failed. See drush help omega-subtheme for usage information.'));
      return FALSE;
  	}
  	else {
  		drush_log(dt('The theme directory: '. $theme_dir .' does not exist. It was created for you. I hope you don\'t mind!!'), 'ok');
  	}
  }
  if (is_dir($site_dir .'/'. $name)) {
  	drush_set_error(dt('The destination theme directory: '. $site_dir .' already exists. Please specify another theme name. See drush help omega-subtheme for usage information.'));
    return FALSE;
  }
  
  switch ($type) {
    case 'html5':
      // copy the starterkit directory to the new location
      $exec = 'rsync -r ' . $omega_path .'/* '. $theme_dir .'/'. $name;
      // replace instances of omega_starterkit in all php files
      //$exec .= '; sed -i.bak s/omega_starterkit/'. $name .'/ '. $theme_dir .'/'. $name .'/template.php';
      //$exec .= '; sed -i.bak s/omega_starterkit/'. $name .'/ '. $theme_dir .'/'. $name .'/theme-settings.php';
      // move the .info file
      $exec .= '; mv '. $theme_dir .'/'. $name .'/starterkit_omega_html5.info '. $theme_dir .'/'. $name .'/' . $name .'.info';
      // change the name of the theme in the .info file
      $exec .= '; sed -i.bak s/"Omega HTML5 Starterkit"/"'. $name_long .'"/ '. $theme_dir .'/'. $name .'/*.info';
      // remove the .bak files. I don't know how to run sed without the 
      $exec .= '; rm -rf ' . $theme_dir .'/'. $name .'/*.bak';
      drush_log(dt('HTML5 Omega Subtheme: '. $name_long .' ('. $name .') created and configured for usage.'), 'ok');
    break;
    case 'xhtml':
      // copy the starterkit directory to the new location
      $exec = 'rsync -r ' . $omega_path .'/* '. $theme_dir .'/'. $name;
      // replace instances of omega_starterkit in all php files
      //$exec .= '; sed -i.bak s/omega_starterkit_xhtml/'. $name .'/ '. $theme_dir .'/'. $name .'/template.php';
      //$exec .= '; sed -i.bak s/omega_starterkit_xhtml/'. $name .'/ '. $theme_dir .'/'. $name .'/theme-settings.php';
      // move the .info file
      $exec .= '; mv '. $theme_dir .'/'. $name .'/starterkit_omega_xhtml.info '. $theme_dir .'/'. $name .'/' . $name .'.info';
      // change the name of the theme in the .info file
      $exec .= '; sed -i.bak s/"Omega XHTML Starter Kit"/"'. $name_long .'"/ '. $theme_dir .'/'. $name .'/*.info';
      // remove the .bak files. I don't know how to run sed without the 
      $exec .= '; rm -rf ' . $theme_dir .'/'. $name .'/*.bak';
      drush_log(dt('XHTML Omega Subtheme: '. $name_long .' ('. $name .') created and configured for usage.'), 'ok');
    break;
  }
  return $exec;
}
