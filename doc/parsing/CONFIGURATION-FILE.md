# Configuration file

The configuration file is a simple text file that contains the configuration of the server. It is composed of a series of directives, each directive is on a single line. A directive starts with a keyword, followed by arguments.

## Directives

The configuration file must be in YAML.

<table>
<thead>
  <tr>
    <th colspan="3" style="text-align: center;"><span style="font-weight:bold;">Server Mandatory</span></th>
  </tr>
</thead>
<tbody>
  <tr>
    <th style="text-align: center;">Key</th>
    <th style="text-align: center;">Type</th>
    <th style="text-align: center;">Value</th>
  </tr>
  <tr>
    <td>server_name</td>
    <td>string</td>
    <td>name to connect to the server</td>
  </tr>
  <tr>
    <td>address IP</td>
    <td>string</td>
    <td>server ip address</td>
  </tr>
  <tr>
    <td>port</td>
    <td>int</td>
    <td>port where the server will receive the requests</td>
  </tr>
</tbody>
<thead>
  <tr>
    <th colspan="3" style="text-align: center;"><span style="font-weight:bold;">Server Content</span></th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>routes</td>
    <td>map&#60;string, string&#62;</td>
    <td>map of all routes replace/path</td>
  </tr>
</tbody>
<thead>
  <tr>
    <th colspan="3" style="text-align: center;"><span style="font-weight:bold;">Default values for all routes (can be redefine individually)</span></th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>root</td>
    <td>string</td>
    <td>Root path of the server</td>
  </tr>
  <tr>
    <td>index</td>
    <td>string</td>
    <td>Names of the index file for all routes</td>
  </tr>
  <tr>
    <td>max_body_size</td>
    <td>int</td>
    <td>Max length for client body size</td>
  </tr>
  <tr>
    <td>error_page</td>
    <td>string</td>
    <td>Path to default error page</td>
  </tr>
  <tr>
    <td>allowed_methods</td>
    <td>Array</td>
    <td>Allowed http methods for all routes</td>
  </tr>
  <tr>
    <td>cgi_bin</td>
    <td>string</td>
    <td>Path to CGI executable file for all routes</td>
  </tr>
  <tr>
    <td>directory_listing</td>
    <td>bool</td>
    <td>On/off directory listing</td>
  </tr>
  <tr>
    <td>cgi_extensions</td>
    <td>array</td>
    <td>File extensions where CGI will be executed</td>
  </tr>
  <tr>
    <td>upload_dir</td>
    <td>string</td>
    <td>Path to save uploaded file from all routes</td>
  </tr>
</tbody>
<thead>
  <tr>
    <th colspan="3" style="text-align: center;"><span style="font-weight:bold;">Route content</span></th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>route_path</td>
    <td>array</td>
    <td>Path of this route</td>
  </tr>
  <tr>
    <td>root</td>
    <td>string</td>
    <td>Redefine the root for this route</td>
  </tr>
  <tr>
    <td>max_body_size</td>
    <td>int</td>
    <td>Redefine max length for client body size for this route</td>
  </tr>
  <tr>
    <td>index</td>
    <td>string</td>
    <td>names of the index file for this routes</td>
  </tr>
  <tr>
    <td>allowed_methods</td>
    <td>Array</td>
    <td>Allowed http methods for this route</td>
  </tr>
  <tr>
    <td>cgi_bin</td>
    <td>string</td>
    <td>Path to CGI executable file for this route</td>
  </tr>
  <tr>
    <td>cgi_extensions</td>
    <td>array</td>
    <td>File extensions where CGI will be executed</td>
  </tr>
  <tr>
    <td>upload_dir</td>
    <td>string</td>
    <td>Path to save uploaded file for this route</td>
  </tr>
</tbody>
</table>



*Here's some docs for YAML*
>https://learn.getgrav.org/16/advanced/yaml&emsp;&emsp;Basic YAML syntax introduction

[Back to summary](../SUMMARY.md)