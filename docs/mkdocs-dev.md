# MkDocs development guide

For full documentation visit [mkdocs.org](https://www.mkdocs.org).

## Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.

## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.

## Documentation Flow

This section defines necessary steps to wok with the [MkDocs Material Framework](https://squidfunk.github.io/mkdocs-material/).<br>
The framework presents a static site generator with documentation written in Markdown.<br>
All the docs are configured with a YAML configuration file.

There are two options for working with MkDocs:

* MkDocs via Podman/Docker
* MkDocs via Python PIP

## MkDocs via Podman/Docker

### Prerequisites

* [Podman](https://podman.io/) or [Docker](https://www.docker.com/get-started/)
* [Make](https://man7.org/linux/man-pages/man1/make.1.html)
* [mkdocs cli](https://www.mkdocs.org/)

### Workflow

1. Clone the edp-install repository to your local folder.

2. Run the following command:

    ```
    make docs
    ```

    For Docker

    ```
    make docs ENGINE=docker
    ```

3. Enter the [http://localhost:8000](/) address in the browser and check that documentation pages are available.

4. Open the editor, navigate to the docs/ directory and make necessary changes. All the changes will be updated dynamically at [http://localhost:8000](/).

5. Create a merge request with changes or deploy to GitHub pages manually:

    ```
    mkdocs gh-deploy --force
    ```

## MkDocs via Python PIP

### Prerequisites

* [Python](https://www.python.org/)
* [Python PIP](https://pypi.org/project/pip/)
* [mkdocs cli](https://www.mkdocs.org/)

### Workflow

1. Run the following command:

    ```bash
    pip install -r  docker-image/mkdocs/requirements.txt
    ```

3. Run a local development server:

    ```
    mkdocs serve --dev-addr 0.0.0.0:8000
    ```

    !!! Note ""

          For Windows:

          ```psh
          python -m mkdocs serve --dev-addr 0.0.0.0:8000
          ```

4. Enter the [http://localhost:8000](/) address in the browser and check that documentation pages are available.

5. Open the editor, navigate to the docs/ directory and make necessary changes. All the changes will be updated dynamically at [http://localhost:8000](/).

6. Create a merge request with changes or deploy to GitHub pages manually:

    ```
    mkdocs gh-deploy --force
    ```
