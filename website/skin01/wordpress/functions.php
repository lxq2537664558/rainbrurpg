<?php
if ( function_exists('register_sidebar') )
    register_sidebar();

/**
 * Get our wp_nav_menu() fallback, wp_page_menu(), to show a home link.
 */
function rainbrurpg_page_menu_args( $args )
{
	$args['show_home'] = true;
	return $args;
}

function rainbrurpg_setup()
{
  // Add default posts and comments RSS feed links to <head>.
  add_theme_support( 'automatic-feed-links' );

}

add_filter( 'wp_page_menu_args', 'rainbrurpg_page_menu_args' );
add_action( 'after_setup_theme', 'rainbrurpg_setup' );

?>
