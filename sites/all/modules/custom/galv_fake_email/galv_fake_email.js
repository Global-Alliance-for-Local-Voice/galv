/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

    // To understand behaviors, see https://drupal.org/node/756722#behaviors
    Drupal.behaviors.galv_fake_email = {
        attach: function (context, settings) {

            var value = $('#edit-name').val();

            $('#edit-name').change(function () {
              if (this.value != '') {
                  // Check if the checkbox is checked.
                  // So that in case the username changes and is now different, the fake email is still correct.
                  if ($('#edit-fake-email:checkbox:checked').length > 0) {
                      // Match checkbox to name if it changes.
                      $('#edit-mail').val($('#edit-name').val() + 'anon@galv.world');
                  }
              }
              else {
                  // Make the email value 'anon@galv.world'.
                  $('#edit-mail').val('anon@galv.world');
              }
            });



            $('#edit-fake-email').click(function() {
                if ($('#edit-fake-email:checkbox:checked').length > 0 && $('#edit-name') != '') {
                    // Populate fake username field
                    $('#edit-mail').val($('#edit-name').val() + 'anon@galv.world');
                    // disable $('#edit-mail')
                    $('#edit-mail')
                        .each(function() {
                            alert("After clicking this button, you will no longer be able to enter your E-mail address.  An anonymous email address will be " +
                                "generated when you enter your Username.");
                        })
                        .attr("readonly", "readonly")
                        .addClass("message").removeClass("test");
                }
                else if ($('#edit-fake-email:checkbox:checked').length == 0) {
                    // Set email to blank if checkbox is unchecked.
                    $('#edit-mail').val('');
                    // enable $('#edit-mail')
                    $('#edit-mail')
                        .attr("readonly", false)
                        .removeClass("message").addClass("test");
                }

            });

        }

    };

})(jQuery, Drupal, this, this.document);