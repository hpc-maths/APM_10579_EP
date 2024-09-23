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
        oop: resolve(__dirname, 'compilation/index.html'),
        value_semantics: resolve(__dirname, 'value_semantics/index.html'),
        memory: resolve(__dirname, 'memory/index.html'),
        polymorphism: resolve(__dirname, 'polymorphism/index.html'),
        templates: resolve(__dirname, 'templates/index.html'),
      },
    },
  },
})
