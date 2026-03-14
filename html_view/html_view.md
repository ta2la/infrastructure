## common

`type: control`

## text

`control: text`<br/>
`text: TEXT`
`cmd: CMD`

obsolete - `text: <hup>|<space>`
obsolete - `TC;CT; == type: control;control: text`<br/>
`TEXT: == type: control;control: text; text:`

## button

`control: button`<br/>
`text: TEXT`<br/>
`cmd: CMD`<br/>
`mark:`<br/>
`icon: PATH`<br/>
`color: R,G,B`<br/>
`active:`<br/>
`iconsize: SIZE`<br/>

obsolete - `TC;CB; == type: control;control: button`<br/>
`BUTTON: == type: control;control: button; cmd:`

## edit

`control: edit`<br/>
`text: TEXT`
`cmd: CMD "$TEXT"`

obsolete - `TC;CE; == type: control;control: button`
`EDIT: == type:control;control:edit;cmd:`

## spacer

`control: spacer`<br/>
`spacer: offset_x|newline|relative_y|minx`<br/>
`value: <- spacer: offset_x, relative_x, minx`

`NEWLINE == type: control;control:spacer; spacer:newline`
`SPACE == type:control;control:spacer; spacer:offset_x;value:5;`
`TAB: == type: control;control:spacer; spacer:offset_x`


