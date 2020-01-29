# Flask with SQLAlchemy

Link: https://www.youtube.com/watch?v=Z1RJmh_OqeA

## Environment

Install following in your env:
`pip install flask flask-sqlalchemy`

## Basic App

```python
from flask import Flask

app = Flask(__name__)

@app.route('/')
def index():
    return "HelloWorld!"

if __name__ == "__main__":
    app.run(debug=True)
```