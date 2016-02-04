# japavocards
Japanese vocabulary training application.

Japavocards is written in C++ with SDL2. To build it you will need to clone and build the repositories for "libdansdl2" and "herramientas_proyecto". Once you've done that, configure the routes in the "makefile_linux" or "makefile_win" files and you're ready to "make -f makefile_linux" or "make -f makefile_win".

There are two parts to the application: the front end and the backend.

The front end consists on the application itself. It will show you japanes script and, at the touch of a key, show you the romaji and translation for it. Since this is an educational assist tool it does not track whether you guessed the word or not (or even if you tried to guess at all): just runs the carrousel of words over and over, as if they were vocabulary cards.

The application does allow for:

- Shuffle the words in each run so every exercise is slightly different (words are all the same, order is different).

The application will allow for:

- Filter the words used in the exercise: all words, all words with a set of labels, all unlabeled words...
- Choose the interface and translation language.
- Choose between continuous exercise (endless loop of words) or a finite set (chosen words, once).
- Allow for reverse translation (from the translation to the japanese words).
- Allow and disallow the romaji text (so you can practice your reading skills).

Probably will also:

- Allow for background changes smuggling code from "KanaFun".
- Allow for window size changes smuggling more code from "KanaFun".

The backend is a command line interface to manage the application database. To start the CLI:

	./japavocards.out --cli [--file path_to_database_file]

The CLI allows for:

- Creating, updating and deleting languages, labels and words.
- Set the interface and canonical (the language used for translations) languages separately.
- Set labels to words.
- Search for words or labels.
- Filter words by label.
- Enable autolabelling: choose a set of labels and automatically set them to newly created words.

When working with the CLI take into account that:

- Language acronyms shall not be repeated (you will be asked for one).
- Label keys cannot be repeated (you will be asked for one).
- Japanese text for the words cannot be repeated.
- Each time you save a backup file with the previous content is created in the data/app/ directory.

Thanks to:

- Ed Merritt for the Akashi font.
- Kagura Zakayuzu for the Yuzu Pop A font.
