# mod_cluster_adapter
module to replace mod_proxy_cluster modules and use mod_balancer logic
# to build (use an httpd trunk installation)
apxs -c mod_cluster_adapter.c to build. 
apxs -i -a -c mod_cluster_adapter.c to install.
