pandoc_engine = --pdf-engine=xelatex
pandoc_options = -V geometry:"top=2cm, bottom=1.5cm, left=2cm, right=2cm" \
                 -V colorlinks -V urlcolor=NavyBlue -V toccolor=Red \
				 --filter pandoc-crossref

bz :
	pandoc bz.md ${pandoc_engine} ${pandoc_options} -o bz.pdf

barnes-hut :
	pandoc barnes-hut.md ${pandoc_engine} ${pandoc_options} -o barnes-hut.pdf

dnn :
	pandoc dnn.md ${pandoc_engine} ${pandoc_options} -o dnn.pdf

interpolation :
	pandoc interpolation.md ${pandoc_engine} ${pandoc_options} -o interpolation.pdf

pde1d :
	pandoc pde1d_solver.md ${pandoc_engine} ${pandoc_options} -o pde1d_solver.pdf

depixel :
	pandoc depixelizing.md ${pandoc_engine} ${pandoc_options} -o depixelizing.pdf

all : bz barnes-hut dnn interpolation pde1d depixel