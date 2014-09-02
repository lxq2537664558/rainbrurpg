<?php
/**
 * The main template file.
 *
 * This is the most generic template file in a WordPress theme
 * and one of the two required files for a theme (the other being style.css).
 * It is used to display a page when nothing more specific matches a query.
 * E.g., it puts together the home page when no home.php file exists.
 * Learn more: http://codex.wordpress.org/Template_Hierarchy
 *
 * @package WordPress
 * @subpackage Twenty_Eleven
 */

get_header(); ?>

<?php /* Search for the ADDED word to see differences between . and .. */ ?>

<div id="patternScreen">
  <div id="patternPageShadow">
    <div id="patternPage">
      <div id="patternWrapper">
        <div id="patternOuter">
          <div id="patternFloatWrap">
            <div id="patternMain">
              <div id="content" role="main">

        <?php /* The loop: see http://codex.wordpress.org/The_Loop */ ?>
			  
        <!-- Start the Loop. -->
          <?php if ( have_posts() ) : while ( have_posts() ) : the_post(); ?>
           <div class="post">

           <!-- Display the Title as a link to the Post\'s permalink. -->
           <header class=post-header>
              <h2><a href="<?php the_permalink() ?>" rel="bookmark" 
                     title="Permanent Link to <?php the_title_attribute(); ?>">
                     <?php the_title(); ?></a></h2>

		 <?php if ( 'post' == get_post_type() ) : ?>
		   <div class="entry-meta">
				<?php /* twentyeleven_posted_on();*/ ?>
			</div><!-- .entry-meta -->
			<?php endif; ?>

			<?php if ( comments_open() && ! post_password_required() ) : ?>
			<div class="comments-link">
				<?php comments_popup_link( '<span class="leave-reply">' . __( 'Reply', 'twentyeleven' ) . '</span>', _x( '1', 'comments number', 'twentyeleven' ), _x( '%', 'comments number', 'twentyeleven' ) ); ?>
			</div>
			<?php endif; ?>

 <!-- Display the date (November 16th, 2009 format) and a link to other posts by this posts author. -->
 <small><?php the_time('F jS, Y') ?> by <?php the_author_posts_link() ?></small>

</header> <!-- post-header -->

 <!-- Display the Post Content in a div box. -->
 <div class="entry">
   <?php the_content('Continue reading <span class="meta-nav">&rarr;</span>'); ?>
 </div>

 <!-- Display a comma separated list of the Post Categories. -->
 <p class="postmetadata">Posted in <?php the_category(', '); ?>&nbsp;

<!-- TAGLIST -->
<?php 
$show_sep = false;
$tags_list = get_the_tag_list( '', __( ', ', 'twentyeleven' ) );
if ( $tags_list ):
  $show_sep = true;
  if ( $show_sep ) : 
    print('<span class=\"sep\"> | </span>');
  endif; 
  printf( __( '<span class="%1$s">Tagged</span> %2$s', 'twentyeleven' ),
	  'entry-utility-prep entry-utility-prep-tag-links', $tags_list );
  $show_sep = true; 
  printf('</span>'); 
endif; 
?>
<!-- End of TAGLIST -->

<!-- Comments -->
<?php if ( comments_open() ) : ?>
   <span class="sep"> | </span>
      <span class="comments-text">
      <?php comments_popup_link( 'Leave a reply',  
				 '<b>1</b> Reply', 
				 '<b>%</b> Replies' ); ?>
</span>
<?php endif; // End if comments_open() ?>
<!-- End of Comments -->

<?php edit_post_link( __( 'Edit', 'twentyeleven' ), '<span class="edit-link">', '</span>' ); ?>

</p> <!-- closes the postmetadata paragraph-->
 </div> <!-- closes the first div box -->

 <!-- Stop The Loop (but note the "else:" - see next line). -->
 <?php endwhile; else: ?>

 <!-- The very first "if" tested to see if there were any Posts to -->
 <!-- display.  This "else" part tells what do if there were not any. -->
 <p>Sorry, no posts matched your criteria.</p>

 <!-- REALLY stop The Loop. -->
 <?php endif; ?>

              </div> <!-- closes content::main -->
	    </div> <!-- closes patternMain -->
	   <div id="patternSideBar">
	     <div id="patternSideBarContents">
	        <?php get_sidebar(); ?>
             </div> <!-- closes patternSideBarContents -->
	    </div> <!-- closes patternSideBar -->
	   <div id="clear">&nbsp;</div>

<!-- ADDED --></div> <!-- closes patternFloatWrap -->
<!-- ADDED --></div> <!-- closes patternOuter -->
<!-- ADDED --></div> <!-- closes patternWrapper -->

</div><!-- closes skin01-content -->

<?php get_footer(); ?>
<!-- ADDED --></div> <!-- closes patternPage -->
<!-- ADDED --></div> <!-- closes patternPageShadow -->
<!-- ADDED --></div> <!-- closes patternScreen -->



</body>
</html>