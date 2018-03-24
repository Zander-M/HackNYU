"""
requests test
Author: Zander.M
Created at: 15:54, 03, 23, 2018,

"""
import requests
from PIL import Image
import json
import io
postConfig = {
	"init": {"name": "camera.startSession","parameters": {}},
	"setOption": {"name": "camera.setOptions","parameters": {"options": {"clientVersion": 2}}},
	"setProperty": {"name": "camera.getOptions","parameters": {"optionNames": ["fileFormat","fileFormatSupport"]}},
	"photoSettings": {"name": "camera.setOptions","parameters":{"options":{"fileFormat":{"type": "jpeg","width": 2048, "height": 1024}}}},
	"takePicture": {"name": "camera.takePicture","parameters": {}},
	"getLive": {"name": "camera._getLivePreview", "parameters": {}},
	"getPicture": {"name": "camera.getImage","parameters": {}},
	"endSession": {"name": "camera.closeSession", "parameters": {}},
}
camExecHTTP = 'http://192.168.1.1/osc/commands/execute'
camStateHTTP = 'http://192.168.1.1/osc/state'


class Camera:
	pic = []

	def __init__(self, config, exe, state):
		self.config = config
		self.exe = exe
		self.state = state
		self.info = requests.post(exe, data=json.dumps(config['init'])).json()  # initiate a session
		print(self.info)
		self.sessionId = self.info['results']['sessionId']  # record sessionId
		config['setOption']['sessionId'] = self.sessionId
		requests.post(exe, data=json.dumps(config['setOption']))
		requests.post(exe, data=json.dumps(config['setProperty']))

	def camset(self):
		self.config['photoSettings']['parameters']['sessionId'] = self.sessionId
		re = requests.post(self.exe, data=json.dumps(self.config['photoSettings']))
		print(re.json())

	def takepic(self):  # take a picture
		self.config['takePicture']['parameters']['sessionId'] = self.sessionId
		requests.post(self.exe, data=json.dumps(self.config['takePicture'])).json()
		uri = requests.post(self.state).json()['state']['_latestFileUri']
		print(uri)
		self.pic.append(uri)

	def getlive(self):  # get liveStream
		self.config['getLive']['parameters']['sessionId'] = self.sessionId

	def getpic(self):
		self.config["getPicture"]['parameters']['fileUri'] = self.pic[-1]
		uri = self.config["getPicture"]
		img = requests.post(self.exe, data=json.dumps(uri))
		pic = Image.open(io.BytesIO(img.content))
		return pic

	def endsession(self):
		self.config['endSession']['parameters']['sessionId'] = self.sessionId
		requests.post(self.exe, data=json.dumps(self.config['endSession']))


def main():
	cam = Camera(postConfig, camExecHTTP, camStateHTTP)
	cam.camset()
	# cam.takepic()
	# pic = cam.getpic()
	cam.endsession()
	# pic.show()
	return pic

if __name__ == '__main__':
	main()


# Theta S API FUNCTIONS

# Start a session
# POST /osc/commands/execute
# {
#     "name": "camera.startSession",
#     "parameters": {}
# }

# SPICIFY API VERSION IMPORTANT!!!!!
# POST /osc/commands/execute
# {
#     "name": "camera.setOptions",
#     "parameters": {
#         "sessionId": "SID_0001",
#         "options": {
#             "clientVersion": 2
#         }
#     }
# }

# CHECK STATE
# POST /osc/state

# ACQUIRE AND SET PROPERTIES
# POST /osc/commands/execute
# {
#     "name": "camera.getOptions",
#     "parameters": {
#         "optionNames": [
#             "fileFormat",
#             "fileFormatSupport"
#         ]
#     }
# }

# SHOOTING SETTINGS
# POST /osc/commands/execute
# {
#     "name": "camera.setOptions",
#     "parameters": {
#         "options": {
#             "fileFormat": {
#                 "type": "jpeg",
#                 "width": 2048,
#                 "height": 1024
#             }
#         }
#     }
# }

# TAKE A PICTURE
# POST /osc/commands/execute
# {
#     "name": "camera.takePicture"
# }

# GET FILE
# GET /files/abcde/100RICOH/R0010005.JPG
