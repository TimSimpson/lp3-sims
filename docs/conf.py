# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
project = 'lp3-sims'
copyright = '2020, Tim Simpson'
author = 'Tim Simpson'

# The short X.Y version
version = ''
# The full version, including alpha/beta/rc tags
release = ''

extensions = [
]

templates_path = ['_templates']
source_suffix = ['.rst', '.md', '.mrst']
master_doc = 'index'
language = None
exclude_patterns = []
pygments_style = 'monokai'
html_theme = 'traditional'
html_static_path = ['_static']
htmlhelp_basename = 'lp3-sims-doc'
latex_elements = {
}
latex_documents = [
    (master_doc, 'lp3-sims.tex', 'lp3-sims Documentation',
     'Tim Simpson', 'manual'),
]
man_pages = [
    (master_doc, 'lp3-core', 'lp3-sims Documentation',
     [author], 1)
]
texinfo_documents = [
    (master_doc, 'lp3-sims', 'lp3-sims Documentation',
     author, 'lp3-sims', 'One line description of project.',
     'Miscellaneous'),
]
