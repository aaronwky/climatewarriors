function initViz() {
    var containerDiv = document.getElementById("tableauViz"),
    url = "https://public.tableau.com/views/Trash_Dashboard/Dashboard12?:language=en-US&publish=yes&:sid=&:display_count=n&:origin=viz_share_link";

    var viz = new tableau.Viz(containerDiv, url);
}