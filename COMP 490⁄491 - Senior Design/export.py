from mitmproxy.io import FlowReader
from mitmproxy import flow
from mitmproxy import http
from mitmproxy import net

filename = 'requests.mitm'
with open(filename, 'rb') as fp:
    reader = FlowReader(fp)
    for flow in reader.stream():
        if type(flow.response) is not type(None):
            if (flow.response.status_code == 200):
                try:
                    if flow.response.headers['content-type'] is not None:
                        if flow.response.headers['content-type'].startswith('text/html'):
                            print(flow.response.content)
                except KeyError:
                    continue 
