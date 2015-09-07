$(document).ready(function() {
	var mute_audio = false;
	var mute_video = false;
	
	/** mute audio button */
	$("#mute-audio").on("click", function() {
		if(mute_audio == false) {
			$("#mute-audio").css( "background-color", "red" );
			mute_audio = true;
			webrtc.mute();
		} else {
			$("#mute-audio").css( "background-color", "green" );
			mute_audio = false;
			webrtc.unmute();
		}
	});

	/** disable video button */
	$("#mute-video").on("click", function() {
		if(mute_video == false) {
			$("#mute-video").css( "background-color", "red" );
			mute_video = true;
			webrtc.pauseVideo();					
		} else {
			console.log("enable-video");
			$("#mute-video").css( "background-color", "green" );
			mute_video = false;
			webrtc.resumeVideo();
		}
	});

	/** enable sortable remote videos via drag and drop */
	$("#sortable").sortable({revert: true});
	$("ul, li").disableSelection();
});		
