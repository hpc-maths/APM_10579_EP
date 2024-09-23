// vite.config.js
import { resolve } from 'path'
import { defineConfig } from 'vite'

export default defineConfig({
    base: 'https://hpc-maths.github.io/APM_10579_EP/',
    build: {
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        basics: resolve(__dirname, 'basics/index.html'),
        functional_stl: resolve(__dirname, 'functional_stl/index.html'),
        compilation: resolve(__dirname, 'compilation/index.html'),
      },
    },
  },
})
