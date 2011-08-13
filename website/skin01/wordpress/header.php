<?php
/*
This code mainly based the twentyeleven's one.
*/

/**
  * The Header for our theme.
  *
  * Displays all of the *head* section and everything up till *div id="main"*
  *
  * @package WordPress
  * @subpackage RainbruRPG
  * @since RainbruRPG 1.0
  */
?>
<!DOCTYPE html>
<html <?php language_attributes(); ?>>
<head>
<meta charset="<?php bloginfo( 'charset' ); ?>" />
<title><?php
        /*
         * Print the <title> tag based on what is being viewed.
         */
        global $page, $paged;

        wp_title( '|', true, 'right' );

        // Add the blog name.
        bloginfo( 'name' );

        // Add the blog description for the home/front page.
        $site_description = get_bloginfo( 'description', 'display' );
        if ( $site_description && ( is_home() || is_front_page() ) )
                echo " | $site_description";

        // Add a page number if necessary:
        if ( $paged >= 2 || $page >= 2 )
                echo ' | ' . sprintf( __( 'Page %s', 'twentyeleven' ), max( $paged, $page ) );

        ?></title>
<link rel="profile" href="http://gmpg.org/xfn/11" />
<link rel="stylesheet" type="text/css" media="all" href="<?php bloginfo( 'stylesheet_url' ); ?>" />
<link rel="pingback" href="<?php bloginfo( 'pingback_url' ); ?>" />

<?php
        /* We add some JavaScript to pages with the comment form
         * to support sites with threaded comments (when in use).
         */
        if ( is_singular() && get_option( 'thread_comments' ) )
                wp_enqueue_script( 'comment-reply' );

        /* Always have wp_head() just before the closing </head>
         * tag of your theme, or you will break many plugins, which
         * generally use this hook to add elements to <head> such
         * as styles, scripts, and meta tags.
         */
        wp_head();
?>
<link rel="stylesheet" href="../common/skin.css" type="text/css" />
<link rel="stylesheet" href="../common/menu.css" type="text/css" />
<script type="text/javascript" src="https://apis.google.com/js/plusone.js"></script>
<!-- ADDTHIS BUTTON BEGIN -->
<script type="text/javascript">
var addthis_config = {
     pubid: "YOUR-PROFILE-ID"
}
</script>

</head>
<div id="top-box">RainbruRPG
  <div id="google-ad">Google-ad</div>
  <div id="social-networks">
    <g:plusone></g:plusone>
<a href="http://www.addthis.com/bookmark.php?v=250" 
        class="addthis_button"><img 
        src="http://s7.addthis.com/static/btn/v2/lg-share-en.gif" 
        width="125" height="16" border="0" alt="Share" /></a>

<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js"></script>
<!-- ADDTHIS BUTTON END -->

  </div> <!-- social networks-->
</div>
<ul id="nav">
  <li id="nav-1" class="selected"><em><a href="http://www.free-css.com/">Blog</a></em></li>
  <li id="nav-2"><a href="http://www.free-css.com/">Wiki</a>
  </li>
  <li id="nav-3"><a href="http://www.free-css.com/">Servers status</a></li>
  <li id="nav-3"><a href="http://www.free-css.com/">API documentations</a></li>
  <li id="nav-4"><a href="http://www.free-css.com/">Manuals</a></li>
  <li id="nav-5"><a href="http://www.free-css.com/">Forums (sf.net)</a></li>
</ul>
<div id="skin01-content">
  <div id="branding">
   <?php get_search_form(); ?>
  </div>
<nav id="access" role="navigation">
  <h3 class="assistive-text"><?php _e( 'Main menu', 'twentyeleven' ); ?></h3>
  <?php /*  Allow screen readers / text browsers to skip the navigation 
         *  menu and get right to the good stuff. 
         */ ?>
  <div class="skip-link">
    <a class="assistive-text" href="#content" 
       title="<?php esc_attr_e( 'Skip to primary content', 'twentyeleven' ); ?>">
    <?php _e( 'Skip to primary content', 'twentyeleven' ); ?></a></div>
                                <div class="skip-link"><a class="assistive-text" href="#secondary" title="<?php esc_attr_e( 'Skip to secondary content', 'twentyeleven' ); ?>"><?php _e( 'Skip to secondary content', 'twentyeleven' ); ?></a></div>
                                <?php /* Our navigation menu.  If one isn't filled out, wp_nav_menu falls back to wp_page_menu. The menu assiged to the primary position is the one used. If none is assigned, the menu with the lowest ID is used. */ ?>
                                <?php wp_nav_menu( array( 'theme_location' => 'primary' ) ); ?>
                        </nav><!-- #access -->

<div id="main">
<!-- End of the standard header code -->
