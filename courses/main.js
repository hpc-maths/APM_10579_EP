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
// import RevealMenu from 'reveal.js-menu/plugin.js'
import RevealMenu from '/public/plugin.js'

function get_theme_ext(href)
{
  if (href == "/theme/dark.css")
  {
    return ["dark", "light"];
  }
  else {
    return ["light", "dark"];
  }
}

function update_img() {
  var theme = document.getElementById("theme");
  var href = theme.getAttribute("href");
  var theme_name = get_theme_ext(href);
  var el = document.querySelectorAll("#adapt");
  for (var i = 0; i < el.length; i++) {
    var data = el[i].getAttribute("src").replace(theme_name[1], theme_name[0]);
    //console.log(data);

    el[i].setAttribute("src", data);
  }
}

var theme = document.querySelector("#theme");
console.log(theme);
var observer = new MutationObserver(function(mutation){
  //console.log("test");

  update_img();
});

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
    themes: [
      {name: 'dark', theme: '/APM_10579_EP/theme/dark.css'},
      {name: 'light', theme: '/APM_10579_EP/theme/light.css'}
    ],
    themesPath: '/APM_10579_EP/theme',
    path : '/APM_10579_EP/reveal.js-menu'
  },
  // markdown: {
  //   smartypants: true
  // }
})
