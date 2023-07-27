To build

```
docker build -t local/gcc .
docker run --rm -v `pwd`:/usr/src/myapp local/gcc cmake .
docker run --rm -v `pwd`:/usr/src/myapp local/gcc cmake --build .
```
