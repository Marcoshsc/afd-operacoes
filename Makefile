main:
	gcc src/main.c src/strings/stringutil.c src/operations/recognition/recognition.c src/operations/complement/complement.c src/operations/product/product.c src/operations/union/union.c src/operations/intersection/intersection.c src/operations/recognition/recognitionop.c src/operations/visualization/filter/filter.c src/context/context.c src/operations/operations.c src/operations/executor/executor.c src/operations/visualization/visualization.c src/operations/minimization/minimization.c src/operations/dot/dot.c src/afd/afd.c	src/cli/cli.c -o main