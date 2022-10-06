# Anya

A web server written from scratch in C++

<img src="demo.png" width="800"/>

# Usage

```
$ anya --help

Allowed options:
  --help                    produce help message
  -p [ --port ] arg (=3000) set port to run on
  --source-dir arg (=.)     set the source directory
```

```
$ anya --port 3000
[2022-10-06 14:15:31.249] [info] Starting App
[2022-10-06 14:15:31.251] [info] Listening on port 3000
```

# Building

```shell
git clone https://github.com/AnshulKanwar/Anya
cd Anya
make
```

# TODO

- [ ] Express like API
- [ ] Add error handling
- [ ] Add tests
- [x] Add logging
- [ ] Log Custom Objects
- [ ] Colored Logging
- [ ] select()
- [ ] Document Code
- [x] ~Use std::format (C++20)~ used fmt
