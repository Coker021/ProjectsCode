$(document).ready(function () {
    // this function will load all of our header and footer related files into our main HTML document
    $(function () {
        $("#head").load("meta.html");
        $("#header").load("header.html");
        $("#footer").load("footer.html");
    });
});