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
            console.log('got here');
            var value = $('#edit-name').val();

            console.log('got here also');
            console.log (value);
            $('#edit-name').change(function () {
              if (this.value != '') {
                  // Enable fake email checkbox.
                  $('#edit-fake-email').prop('disabled', false);

                  // Check if the checkbox is checked.
                  // So that in case the username changes and is now different, the fake meail is still correct.
                  if ($('#edit-fake-email:checkbox:checked').length > 0) {
                      // Match checkbox to name if it changes.
                      $('#edit-mail').val($('#edit-name').val() + 'anon@galv.world');
                  }
              }
              else {
                  // Disable fake email checkbox if user deletes their Username.
                  $('#edit-fake-email').prop('checked', false);
                  $('#edit-fake-email').prop('disabled', true);
                  // Make the email value blank.
                  $('#edit-mail').val('')
                      .prop("readonly", false)
                      .prop('disabled', false);
              }
            });



            $('#edit-fake-email').click(function() {
                if ($('#edit-fake-email:checkbox:checked').length > 0 && $('#edit-name') != '') {
                    // Populate fake username field
                    $('#edit-mail').val($('#edit-name').val() + 'anon@galv.world');
                    // disable $('#edit-mail')
                    $('#edit-mail')
                        .prop("readonly", "readonly")
                        .prop('disabled', true);
                       // .toggleClass("grey", this.checked);


                }
                else if ($('#edit-fake-email:checkbox:checked').length == 0) {
                    // Set email to blank if checkbox is unchecked
                    $('#edit-mail').val('');
                    // enable $('#edit-mail')
                    $('#edit-mail')
                        .prop("readonly", false)
                        .prop('disabled', false);

                }

            });

        }

    };

})(jQuery, Drupal, this, this.document);