/**
 * @file
 * Initiates Glightbox plugin.
 */
(function($) {

  Backdrop.behaviors.glightbox = {
    attach: function (context, settings) {

      const lightbox = GLightbox({
        openEffect: settings.glightbox.effect_open,
        closeEffect: settings.glightbox.effect_close,
        slideEffect: settings.glightbox.effect_slide,
        moreText: settings.glightbox.ui_more_text,
        moreLength: Number(settings.glightbox.ui_more_length),
        closeButton: Boolean(settings.glightbox.ui_close_btn),
        touchNavigation: Boolean(settings.glightbox.navigation_touch),
        touchFollowAxis: Boolean(settings.glightbox.navigation_touch_follow_axis),
        keyboardNavigation: Boolean(settings.glightbox.navigation_keyboard),
        closeOnOutsideClick: Boolean(settings.glightbox.ui_close_outside),
        descPosition: settings.glightbox.ui_descr_position,
        loop: Boolean(settings.glightbox.navigation_loop),
        zoomable: Boolean(settings.glightbox.navigation_zoomable),
        draggable: Boolean(settings.glightbox.navigation_draggable),
        dragToleranceX: Number(settings.glightbox.navigation_drag_tolerance_x),
        dragToleranceY: Number(settings.glightbox.navigation_drag_tolerance_y),
        dragAutoSnap: Boolean(settings.glightbox.navigation_drag_auto_snap),
        preload: Boolean(settings.glightbox.preload),
      });

    }
  };

})(jQuery);