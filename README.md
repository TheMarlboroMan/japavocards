# japavocards
Japanese vocabulary training application

There are two parts to the application: the front end and the backend.

The front end consists on the application itself.

The backend is a command line interface to manage the application database. To start the CLI:

	japavocard.out --cli [--lan language_id --file path_to_database_file]

The CLI allows for:

- Creating new languages, labels and words.

When inserting data with the CLI take into account that:

- Language acronyms shall not be repeated (you will be asked for one).
- Label keys cannot be repeated (you will be asked for one).
- Japanese text for the words cannot be repeated.
