CFLAGS=-Wall -g

depcheck:
	which ruby 2>/dev/null
	which cucumber 2>/dev/null

deps:
	gem install bundler --pre
	bundle install

test:
	cucumber features/
