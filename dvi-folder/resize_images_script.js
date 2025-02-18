let srcs = [
    "media/gameplay_cli_snake.gif",
    "media/gameplay_cli_tetris.gif",
    "media/gameplay_desktop_snake.gif",
    "media/gameplay_desktop_tetris.gif",
]

function resizeGif(srcField, width) {
    var observer = new MutationObserver(function (mutationsList, observer) {
        for (var mutation of mutationsList) {
            if (mutation.addedNodes.length > 0) {
                var gifImage = document.querySelector(`img[src="${srcField}"]`);
                if (gifImage) {
                    gifImage.width = width;
                    // gifImage.height = 150;
                    observer.disconnect();
                }
            }
        }
    });

    // Start observing the body of the document
    observer.observe(document.body, { childList: true, subtree: true });
}

// Call resizeGif for each source in the srcs array
// for (var i = 0; i < srcs.length; ++i){
//     resizeGif(srcs[i], 650);
// }
//
//
// resizeGif("media/preview.png", 1000);