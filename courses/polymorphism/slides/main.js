import 'reveal.js/dist/reveal.css'
// see available themes in the
// node_modules/reveal.js/dist/theme
//  beige, black, blood, league, moon, night, serif, simple, ...
import 'reveal.js/dist/theme/black.css'
// import 'highlight.js/styles/ir-black.css'
import 'reveal.js/plugin/highlight/monokai.css'
import Reveal from 'reveal.js'
import Markdown from 'reveal.js/plugin/markdown/markdown.esm.js'
import RevealHighlight from 'reveal.js/plugin/highlight/highlight.js'
import RevealMath from 'reveal.js/plugin/math/math.js'

const deck = new Reveal({
  plugins: [Markdown, RevealHighlight, RevealMath.KaTeX]
})
deck.initialize({
  // hash: true,
  // markdown: {
  //   smartypants: true
  // }
})