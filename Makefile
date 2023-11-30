.PHONY: help docs build-docs

CURRENT_DIR=$(shell pwd)

ENGINE?=podman

help:
	@echo "Run 'make docs' or 'make build-docs'"

## check documents http://localhost:8000
docs: mkdocs-image
	@$(ENGINE) run --rm -it \
		-p 8000:8000 \
		-v ${PWD}:/docs \
		--entrypoint mkdocs \
		mkdocs serve --dev-addr=0.0.0.0:8000

build-docs: mkdocs-image
	@$(ENGINE) run --rm -it \
		-v ${PWD}:/docs \
		--entrypoint mkdocs \
		mkdocs build

mkdocs-image:
	@$(ENGINE) build -t mkdocs docker-image/mkdocs
