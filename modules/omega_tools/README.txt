##########################################################################################
      _                _                                  _                     _
   __| | _____   _____| | ___  _ __  _ __ ___   ___ _ __ | |_    __ _  ___  ___| | _____
  / _` |/ _ \ \ / / _ \ |/ _ \| '_ \| '_ ` _ \ / _ \ '_ \| __|  / _` |/ _ \/ _ \ |/ / __|
 | (_| |  __/\ V /  __/ | (_) | |_) | | | | | |  __/ | | | |_  | (_| |  __/  __/   <\__ \
  \__,_|\___| \_/ \___|_|\___/| .__/|_| |_| |_|\___|_| |_|\__|  \__, |\___|\___|_|\_\___/
                              |_|                               |___/
##########################################################################################

##########################################################################################
##### Omega Tools
##########################################################################################
Informational:  http://himer.us/omega960
Project Page:   http://drupal.org/project/omega_tools
Issue Queue:    http://drupal.org/project/issues/omega_tools
Usage Stats:    http://drupal.org/project/usage/omega_tools
Twitter:        http://twitter.com/Omeglicon
Maintainer(s):  Jake Strawn 
                http://himerus.com
                http://developmentgeeks.com
                http://facebook.com/developmentgeeks
                http://drupal.org/user/159141
                http://twitter.com/himerus
##########################################################################################

Omega Tools Information
=======================
The Omega Tools module is a supplemental helper module for the Omega theme. It allows for
creating subthemes via drush on the fly, and exporting and reverting theme settings that 
can then be pasted into the .info file for your Omega subtheme

Drush Subtheme Usage
====================

$ drush omega-subtheme "New Theme Name"
  -- Creates an HTML5 subtheme (new_theme_name) in the default sites/all/themes
  
$ drush omega-subtheme "New Theme Name" html5
  -- Creates an HTML5 subtheme (new_theme_name) in the default sites/all/themes
  
$ drush omega-subtheme "New Theme Name" xhtml
  -- Creates an XHTML subtheme (new_theme_name) in the default sites/all/themes
  
$ drush omega-subtheme "New Theme Name" --destination=example.com
  -- Creates an HTML5 subtheme (new_theme_name) in the default sites/example.com/themes