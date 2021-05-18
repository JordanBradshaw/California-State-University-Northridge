"""Dumps text/html content to stdout"""
import json
from jsonfinder import jsonfinder
import requests
import ast
import gzip
import io
import inspect


class ContentDump:
    def response(self, flow):
        if type(flow.response) is not type(None):
            logfile = open('test4.txt', "a")
            if flow.response.status_code == 200:
                try:
                    if flow.response.headers['content-type'] is not None:
                        if flow.response.headers['content-type'].startswith('text/javascript'):
                            b = bytes(flow.response.content)
                            # Convert to ASCII && Filter whitespace
                            b = b.replace(b"\\u003c", b'<').replace(b"\\u003e", b'>').replace(b'\\"', b'"').replace(
                                b'\\u003d', b'=').replace(b'\xc2\xa0', b'').replace(b'\\u0026', b'&').replace(b'\\n',
                                                                                                              b'').replace(
                                b'\\t', b'').replace(b' ', b'').replace(b'null', b'None')
                            print(str(b))
                            try:
                                b = b[b.index(b'['):b.rindex(b']') + 1]
                                print(b)
                                logfile.write(str(b))
                                logfile.write('\n')
                            except SyntaxError:
                                print("Hello")
                except KeyError:
                    pass


addons = [
    ContentDump()
]
