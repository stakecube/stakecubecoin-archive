package=libcurl
$(package)_version=7.59.0
$(package)_download_path=https://curl.haxx.se/download
$(package)_file_name=curl-$(libcurl_version).tar.bz2
$(package)_sha256_hash=b5920ffd6a8c95585fb95070e0ced38322790cb335c39d0dab852d12e157b5a0
$(package)_dependencies=openssl

define $(package)_set_vars
$(package)_config_opts=--disable-shared --with-ssl
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef
