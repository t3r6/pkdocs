.PHONY: help docs build-docs

CURRENT_DIR=$(shell pwd)

help:
	@echo "Run 'make docs' or 'make build-docs'"

## check documents http://localhost:8000
docs: mkdocs-image
	@podman run --rm -it \
		-p 8000:8000 \
		-v ${PWD}:/docs \
		--entrypoint mkdocs \
		mkdocs serve --dev-addr=0.0.0.0:8000

build-docs: mkdocs-image
	@podman run --rm -it \
		-v ${PWD}:/docs \
		--entrypoint mkdocs \
		mkdocs build

mkdocs-image:
	@podman build -t mkdocs docker-image/mkdocs
