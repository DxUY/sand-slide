class_name HyperLinkLabel
extends RichTextLabel

func _ready() -> void:
	meta_clicked.connect(_on_meta_clicked)

func _on_meta_clicked(meta) -> void:
	OS.shell_open(str(meta))
