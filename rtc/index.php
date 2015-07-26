<html>
    <head>
		<link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/style.css">
		<link rel="stylesheet" href="css/icons.css">
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
        <script src="js/latest.js"></script>		
    </head>
    <body>
        <div class="videoContainer">
            <meter id="localVolume" class="volume" min="-45" max="-20" high="-25" low="-40"></meter>
        </div>
		<div id="icons" class="active">
			<svg id="mute-audio" xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="-10 -10 68 68">
			<title>title</title>
			  <circle cx="24" cy="24" r="34">
				<title>Mute audio</title>
			  </circle>
			  <path class="on" transform="scale(0.6), translate(17,18)" d="M38 22h-3.4c0 1.49-.31 2.87-.87 4.1l2.46 2.46C37.33 26.61 38 24.38 38 22zm-8.03.33c0-.11.03-.22.03-.33V10c0-3.32-2.69-6-6-6s-6 2.68-6 6v.37l11.97 11.96zM8.55 6L6 8.55l12.02 12.02v1.44c0 3.31 2.67 6 5.98 6 .45 0 .88-.06 1.3-.15l3.32 3.32c-1.43.66-3 1.03-4.62 1.03-5.52 0-10.6-4.2-10.6-10.2H10c0 6.83 5.44 12.47 12 13.44V42h4v-6.56c1.81-.27 3.53-.9 5.08-1.81L39.45 42 42 39.46 8.55 6z" fill="white"></path>
			  <path class="off" transform="scale(0.6), translate(17,18)" d="M24 28c3.31 0 5.98-2.69 5.98-6L30 10c0-3.32-2.68-6-6-6-3.31 0-6 2.68-6 6v12c0 3.31 2.69 6 6 6zm10.6-6c0 6-5.07 10.2-10.6 10.2-5.52 0-10.6-4.2-10.6-10.2H10c0 6.83 5.44 12.47 12 13.44V42h4v-6.56c6.56-.97 12-6.61 12-13.44h-3.4z" fill="white"></path>
			</svg>

			<svg id="mute-video" xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="-10 -10 68 68">
			  <circle cx="24" cy="24" r="34">
				<title>Mute video</title>
			  </circle>
			  <path class="on" transform="scale(0.6), translate(17,16)" d="M40 8H15.64l8 8H28v4.36l1.13 1.13L36 16v12.36l7.97 7.97L44 36V12c0-2.21-1.79-4-4-4zM4.55 2L2 4.55l4.01 4.01C4.81 9.24 4 10.52 4 12v24c0 2.21 1.79 4 4 4h29.45l4 4L44 41.46 4.55 2zM12 16h1.45L28 30.55V32H12V16z" fill="white"></path>
			  <path class="off" transform="scale(0.6), translate(17,16)" d="M40 8H8c-2.21 0-4 1.79-4 4v24c0 2.21 1.79 4 4 4h32c2.21 0 4-1.79 4-4V12c0-2.21-1.79-4-4-4zm-4 24l-8-6.4V32H12V16h16v6.4l8-6.4v16z" fill="white"></path>
			</svg>
			<!--
			<svg id="fullscreen" xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="-10 -10 68 68">
			  <circle cx="24" cy="24" r="34">
				<title>Enter fullscreen</title>
			  </circle>
			  <path class="on" transform="scale(0.8), translate(7,6)" d="M10 32h6v6h4V28H10v4zm6-16h-6v4h10V10h-4v6zm12 22h4v-6h6v-4H28v10zm4-22v-6h-4v10h10v-4h-6z" fill="white"></path>
			  <path class="off" transform="scale(0.8), translate(7,6)" d="M14 28h-4v10h10v-4h-6v-6zm-4-8h4v-6h6v-4H10v10zm24 14h-6v4h10V28h-4v6zm-6-24v4h6v6h4V10H28z" fill="white"></path>
			</svg>
			<svg id="hangup" class="hidden" xmlns="http://www.w3.org/2000/svg" width="48" height="48" viewBox="-10 -10 68 68">
			  <circle cx="24" cy="24" r="34">
				<title>Hangup</title>
			  </circle>
			  <path transform="scale(0.7), translate(11,10)" d="M24 18c-3.21 0-6.3.5-9.2 1.44v6.21c0 .79-.46 1.47-1.12 1.8-1.95.98-3.74 2.23-5.33 3.7-.36.35-.85.57-1.4.57-.55 0-1.05-.22-1.41-.59L.59 26.18c-.37-.37-.59-.87-.59-1.42 0-.55.22-1.05.59-1.42C6.68 17.55 14.93 14 24 14s17.32 3.55 23.41 9.34c.37.36.59.87.59 1.42 0 .55-.22 1.05-.59 1.41l-4.95 4.95c-.36.36-.86.59-1.41.59-.54 0-1.04-.22-1.4-.57-1.59-1.47-3.38-2.72-5.33-3.7-.66-.33-1.12-1.01-1.12-1.8v-6.21C30.3 18.5 27.21 18 24 18z" fill="white"></path>
			</svg>
			-->
		</div>			
		<div class="container" id="remotes" name="remotes"></div>		
		<div id="confirm-join-div" class="">
			<div id="room-title">Start a room</div>
			<form id="createRoom">
				<input id="sessionInput"/>
				<button disabled type="submit">Create it!</button>
			</form>
		</div>
        <div class="localScreenContainer">
            <video id="localVideo" oncontextmenu="return false;"></video>
		</div>
		<footer>
			<div id="subTitle"></div>
		</footer>
        <script>
		
			var mute_audio = false;
			var mute_video = false;
		
            // grab the room from the URL
            var room = location.search && location.search.split('?')[1];

            // create our webrtc connection
            var webrtc = new SimpleWebRTC({
                // the id/element dom element that will hold "our" video
                localVideoEl: 'localVideo',
                // the id/element dom element that will hold remote videos
                remoteVideosEl: '',
                // immediately ask for camera access
                autoRequestMedia: true,
                debug: false,
                detectSpeakingEvents: true,
                autoAdjustMic: false
            });

            // when it's ready, join if we got a room from the URL
            webrtc.on('readyToCall', function () {
                // you can name it anything
                if (room) webrtc.joinRoom(room);
            });

            function showVolume(el, volume) {
                if (!el) return;
                if (volume < -45) volume = -45; // -45 to -20 is
                if (volume > -20) volume = -20; // a good range
                el.value = volume;
            }

            // we got access to the camera
            webrtc.on('localStream', function (stream) {
                var button = document.querySelector('form>button');
                if (button) button.removeAttribute('disabled');
                $('#localVolume').show();
            });
            // we did not get access to the camera
            webrtc.on('localMediaError', function (err) {
            });

            // local screen obtained
            webrtc.on('localScreenAdded', function (video) {
                video.onclick = function () {
                    video.style.width = video.videoWidth + 'px';
                    video.style.height = video.videoHeight + 'px';
                };
                document.getElementById('localScreenContainer').appendChild(video);
                $('#localScreenContainer').show();
            });
            // local screen removed
            webrtc.on('localScreenRemoved', function (video) {
                document.getElementById('localScreenContainer').removeChild(video);
                $('#localScreenContainer').hide();
            });

            // a peer video has been added
            webrtc.on('videoAdded', function (video, peer) {
                console.log('video added', peer);
                var remotes = document.getElementById('remotes');
                if (remotes) {
                    var container = document.createElement('div');
                    container.className = 'videoContainer col-lg-3 centered';
                    container.id = 'remote_video_' + webrtc.getDomId(peer);
                    container.appendChild(video);
					
                    // suppress contextmenu
                    video.oncontextmenu = function () { return false; };

                    // resize the video on click
                    //container.ondblclick = function () {
					//	var remote_html = $('#'+container.id).html();
					//	var new_remote_html = remote_html.replace('<video ', '<video id="localVideo" ');
					//	var local_html = $('#backgroundVideo').html();
					//	var new_local_html = local_html.replace('id="localVideo"', '');
					//	$('#backgroundVideo').html(new_remote_html);
					//	$('#'+container.id).html(new_local_html);
                    //};

                    // show the remote volume
                    var vol = document.createElement('meter');
                    vol.id = 'volume_' + peer.id;
                    vol.className = 'volume';
                    vol.min = -45;
                    vol.max = -20;
                    vol.low = -40;
                    vol.high = -25;
                    container.appendChild(vol);
                    
                    // show the ice connection state
                    //if (peer && peer.pc) {
                    //    var connstate = document.createElement('div');
                    //    connstate.className = 'connectionstate';
                    //    container.appendChild(connstate);
                    //    peer.pc.on('iceConnectionStateChange', function (event) {
                    //        switch (peer.pc.iceConnectionState) {
                    //        case 'checking': 
                    //            connstate.innerText = 'Connecting to peer...';
                    //            break;
                    //        case 'connected':
                    //        case 'completed': // on caller side
                    //            $(vol).show();
                    //            connstate.innerText = 'Connection established.';
                    //            break;
                    //        case 'disconnected':
                    //            connstate.innerText = 'Disconnected.';
                    //            break;
                    //        case 'failed':
                    //            connstate.innerText = 'Connection failed.';
                    //            break;
                    //        case 'closed':
                    //            connstate.innerText = 'Connection closed.';
                    //            break;
                    //        }
                    //    });
                    //}
                    remotes.appendChild(container);
                }
            });
            // a peer was removed
            webrtc.on('videoRemoved', function (video, peer) {
                console.log('video removed ', peer);
                var remotes = document.getElementById('remotes');
                var el = document.getElementById(peer ? 'container_' + webrtc.getDomId(peer) : 'localScreenContainer');
                if (remotes && el) {
                    remotes.removeChild(el);
                }
            });

            // local volume has changed
            webrtc.on('volumeChange', function (volume, treshold) {
				if(mute_audio == false) {
					showVolume(document.getElementById('localVolume'), volume);
				}
            });
            // remote volume has changed
            webrtc.on('remoteVolumeChange', function (peer, volume) {
                //showVolume(document.getElementById('volume_' + peer.id), volume);
            });

            // local p2p/ice failure
            webrtc.on('iceFailed', function (peer) {
                var connstate = document.querySelector('#container_' + webrtc.getDomId(peer) + ' .connectionstate');
                console.log('local fail', connstate);
                if (connstate) {
                    connstate.innerText = 'Connection failed.';
                    fileinput.disabled = 'disabled';
                }
            });

            // remote p2p/ice failure
            webrtc.on('connectivityError', function (peer) {
                var connstate = document.querySelector('#container_' + webrtc.getDomId(peer) + ' .connectionstate');
                console.log('remote fail', connstate);
                if (connstate) {
                    connstate.innerText = 'Connection failed.';
                    fileinput.disabled = 'disabled';
                }
            });

            // Since we use this twice we put it here
            function setRoom(name) {
                document.querySelector('form').remove();
                //document.getElementById('room-title').innerText = 'Room: ' + name;
				$('#room-title').text('');
				$('#subTitle').text('Link to join: ' + location.href);
                $('body').addClass('active');
            }

            if (room) {
                setRoom(room);
            } else {
                $('form').submit(function () {
                    var val = $('#sessionInput').val().toLowerCase().replace(/\s/g, '-').replace(/[^A-Za-z0-9_\-]/g, '');
                    webrtc.createRoom(val, function (err, name) {
                        console.log(' create room cb', arguments);
                    
                        var newUrl = location.pathname + '?' + name;
                        if (!err) {
                            history.replaceState({foo: 'bar'}, null, newUrl);
                            setRoom(name);
                        } else {
                            console.log(err);
                        }
                    });
                    return false;          
                });
            }

            var button = document.getElementById('screenShareButton'),
                setButton = function (bool) {
                    button.innerText = bool ? 'share screen' : 'stop sharing';
                };
            if (!webrtc.capabilities.screenSharing) {
                button.disabled = 'disabled';
            }
            webrtc.on('localScreenRemoved', function () {
                setButton(true);
            });

            setButton(true);

            button.click(function () {
                if (webrtc.getLocalScreen()) {
                    webrtc.stopScreenShare();
                    setButton(true);
                } else {
                    webrtc.shareScreen(function (err) {
                        if (err) {
                            setButton(true);
                        } else {
                            setButton(false);
                        }
                    });
                    
                }
            });
        </script>
		
		<script>			
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
		</script>
		
		<script>
			$('#localVideo').css({'left':'0px'});
		</script>
    </body>
</html>