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

function ueb_add_head_link() {
  // Add support for the Universal Edit Button
  // see http://universaleditbutton.org/Wordpress_plugin
  if( is_single() || is_page() ) {
    global $post;
    switch ($post->post_type) {
    case 'attachment':
      return;
    case 'page':
      if(!current_user_can( 'edit_page', $post->ID ) ) return;
      break;
    case 'post':
      //    default:
      if (!current_user_can( 'edit_post', $post->ID ) ) return;
      break;
    }
    
    echo '<link rel="alternate" type="application/x-wiki" title="Edit this page" href="' . get_edit_post_link($post->ID) . "\" />\n";
  }
}


add_filter( 'wp_page_menu_args', 'rainbrurpg_page_menu_args' );
add_action( 'after_setup_theme', 'rainbrurpg_setup' );
add_action( 'wp_head', 'ueb_add_head_link' );
?>
