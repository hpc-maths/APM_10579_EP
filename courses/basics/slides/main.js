import 'reveal.js/dist/reveal.css'
// see available themes in the
// node_modules/reveal.js/dist/theme
//  beige, black, blood, league, moon, night, serif, simple, ...
import 'highlight.js/styles/github.css'
import 'reveal.js-menu/menu.css'

import Reveal from 'reveal.js'
import Markdown from 'reveal.js/plugin/markdown/markdown.esm.js'
import RevealHighlight from 'reveal.js/plugin/highlight/highlight.js'
import RevealMath from 'reveal.js/plugin/math/math.js'
import RevealMenu from './plugin.js'

function get_theme_ext(href)
{
  if (href == "/theme/dark.css")
  {
    return "dark";
  }
  else {
    return "light";
  }
}

function update_img() {
  var theme = document.getElementById("theme");
  var href = theme.getAttribute("href");
  var theme_name = get_theme_ext(href);
  var el = document.querySelectorAll("#adapt");
  for (var i = 0; i < el.length; i++) {
    var data = el[i].getAttribute("src").split("/");
    console.log(data);
    console.log(data.slice(0, 4).join("/"));

    el[i].setAttribute("src", data.slice(0, 4).join("/") + "/" + theme_name + "/" + data.slice(5).join("/"));
  }
}

var observer = new MutationObserver(function(mutation){
  update_img();
});

var theme = document.querySelector("#theme");

observer.observe(theme, {
  attributes: true,
  attributeFilter: ["href"],
});


const deck = new Reveal({
  plugins: [Markdown, RevealHighlight, RevealMath.KaTeX, RevealMenu]
})

deck.initialize({
  center: true,
  hash: true,
  menu: {
    themes: true,
    themes: [
      {name: 'dark', theme: '/theme/dark.css'},
      {name: 'light', theme: '/theme/light.css'}
    ],
    path: 'node_modules/reveal.js-menu/',
  },
  // markdown: {
  //   smartypants: true
  // }
})