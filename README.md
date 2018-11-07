# mod_cluster_adapter
module to replace mod_proxy_cluster modules and use mod_balancer logic

# to build (use an httpd trunk installation)
apxs -c mod_cluster_adapter.c to build. 
apxs -i -a -c mod_cluster_adapter.c to install.

# Configuration
```
LoadModule proxy_balancer_module modules/mod_proxy_balancer.so
LoadModule mod_cluster_adapter_module modules/mod_cluster_adapter.so

<Proxy balancer://mycluster>
    BalancerMember http://localhost:8080
</Proxy>
```

# Test
curl -v http://localhost:8000/toto
